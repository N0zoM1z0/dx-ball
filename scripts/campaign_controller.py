"""Mouse choices from observed gameplay state; no game-memory writes."""

import struct


CONTACT_BIASES = (0.08, -0.18, 0.30, -0.34, 0.16, -0.05)
DECISIONS_PER_CONTACT_BIAS = 100


def choose_greatest_y(state, step, lookahead=2):
    balls = state.get('balls') or []
    width = state['paddle_width']
    falling = [ball for ball in balls if ball['dy'] > 0 and not ball['attached']]
    ball = max(falling, key=lambda value: value['y']) if falling else (balls[0] if balls else None)
    return _choose_for_ball(state, step, ball, lookahead)


def _choose_for_ball(state, step, ball, lookahead):
    width = state['paddle_width']
    center = state['paddle_x']
    urgent = ball is not None and ball['dy'] > 0 and ball['y'] > 390
    if ball is not None:
        center = ball['x'] + ball['width'] / 2 + ball['dx'] * lookahead
    # Vary contact offsets across the original rebound's quantized angle bins.
    # step counts caller decisions; it is not a wall-clock or frame promise.
    bias = width * CONTACT_BIASES[(step // DECISIONS_PER_CONTACT_BIAS) % len(CONTACT_BIASES)]
    desired = center + bias
    lower, upper = width / 2 + 21, 618 - width / 2
    hazards = []
    for bonus in state.get('bonuses') or []:
        if bonus['kind'] in (11, 13, 16) and bonus['y'] + bonus['height'] > 395:
            x = bonus['x'] + bonus['dx'] * lookahead
            hazards.append((x - width / 2 + 3, x + bonus['width'] + width / 2 - 3))
        elif not urgent and bonus['kind'] in (0, 2, 5, 7, 8, 10, 12, 18) and bonus['y'] > 380:
            desired = bonus['x'] + bonus['width'] / 2 + bonus['dx'] * lookahead
    candidates = [desired, center, center - width * 0.35, center + width * 0.35, lower, upper]
    candidates += [edge + delta for interval in hazards for edge, delta in
                   ((interval[0], -4), (interval[1], 4))]
    candidates = sorted({round(max(lower, min(upper, x))) for x in candidates},
                        key=lambda x: abs(x - desired))
    for x in candidates:
        if urgent and abs(x - center) > width / 2 + ball['width'] / 2 - 3:
            continue
        if not any(left <= x <= right for left, right in hazards):
            return x
    return round(max(lower, min(upper, center)))


def choose_contact_mouse(state, step, lookahead=2):
    """Prioritize reachable paddle contact; keep bonus lookahead independent.

    Wall projection is used only below the brick field. Future brick hits,
    live sampling delays and simultaneous incompatible contacts remain unknown.
    """
    paddle_y = state.get('paddle_previous_y', 450)
    drift = int(state.get('bonus_3_ticks', 0) != 0)
    contacts = []
    for ball in state.get('balls') or []:
        if ball['attached'] or ball['dy'] <= 0:
            continue
        height = ball['height']
        radius = (7 + height) // 2
        lower = paddle_y + 3 - radius - height // 2
        upper = paddle_y + 3 + radius - height // 2
        velocity = ball['dy'] + drift
        frames = max(1, (lower - ball['y'] + velocity - 1) // velocity)
        if ball['y'] + frames * velocity > upper:
            continue
        contacts.append((frames, ball))
    if not contacts:
        retained = [ball for ball in state.get('balls') or []
                    if ball['attached'] or ball['dy'] <= 0]
        return choose_greatest_y(dict(state, balls=retained), step, lookahead)
    frames, selected = min(contacts, key=lambda value: value[0])
    projected = dict(selected)
    if selected['y'] >= 350:
        x, dx = selected['x'], selected['dx']
        for _ in range(frames):
            x += dx
            if x < 20:
                x, dx = 20, abs(dx)
            if x > 619 - selected['width']:
                x, dx = 619 - selected['width'], -abs(dx)
        projected.update(x=x, dx=0)
    return _choose_for_ball(state, step, projected, lookahead)


def _tail_hit(grid, ball, x, paddle_y, velocity):
    """Bounded center-ray ranking, not a replacement for brick collision."""
    y = paddle_y - ball['height']
    dx, dy = velocity
    for frames in range(1, 201):
        x += dx
        y += dy
        if x < 20:
            x, dx = 20, abs(dx)
        if x > 619 - ball['width']:
            x, dx = 619 - ball['width'], -abs(dx)
        if y < 0:
            y, dy = 0, abs(dy)
        point_y = y if dy < 0 else y + ball['height']
        if 50 <= point_y <= 349:
            column = max(0, min(19, (x + ball['width'] // 2 - 20) // 30))
            row = (point_y - 50) // 15
            if grid[column + row * 20]:
                return dict(frames=frames, column=column, row=row,
                            tile=grid[column + row * 20])
        if dy > 0 and y >= paddle_y - ball['height']:
            break
    return None


def choose_mouse_decision(state, step, lookahead=2):
    """Keep contact safety; rank six choices only for a known sparse tail."""
    scheduled = (step // DECISIONS_PER_CONTACT_BIAS) % len(CONTACT_BIASES)
    fallback = dict(x=choose_contact_mouse(state, step, lookahead), phase=scheduled,
                    scheduled_phase=scheduled, policy='contact')
    balls = state.get('balls') or []
    if (len(balls) != 1 or state['paddle_width'] <= 0
            or state.get('bonuses') or state.get('bonus_3_ticks', 0)
            or state.get('sprite_bank', 0) != 0):
        return fallback
    ball = balls[0]
    if (ball['attached'] or ball['dy'] <= 0 or ball['y'] < 350
            or ball.get('speed') != 9 or ball['width'] != ball['height']
            or ball['width'] not in (5, 9)):
        return fallback
    try:
        grid = bytes.fromhex(state.get('board_tiles', ''))
    except (TypeError, ValueError):
        return fallback
    if len(grid) != 400 or not 2 <= sum(bool(v) for v in grid) <= 8 or 2 in grid:
        return fallback
    paddle_y = state.get('paddle_previous_y', 450)
    radius = (7 + ball['height']) // 2
    lower = paddle_y + 3 - radius - ball['height'] // 2
    upper = paddle_y + 3 + radius - ball['height'] // 2
    frames = max(1, (lower - ball['y'] + ball['dy'] - 1) // ball['dy'])
    if frames > 100 or ball['y'] + frames * ball['dy'] > upper:
        return fallback
    x, dx = ball['x'], ball['dx']
    for _ in range(frames):
        x += dx
        if x < 20:
            x, dx = 20, abs(dx)
        if x > 619 - ball['width']:
            x, dx = 619 - ball['width'], -abs(dx)
    choices = []
    for phase in range(len(CONTACT_BIASES)):
        mouse = choose_contact_mouse(state, phase * DECISIONS_PER_CONTACT_BIAS, lookahead)
        ratio = (x + ball['width'] // 2 - (mouse - state['paddle_width'] // 2)) / state['paddle_width']
        ratio = struct.unpack('<f', struct.pack('<f', ratio))[0]
        # Interior speed9 bins are measured by the original rebound fixtures.
        if ratio <= 0.07 or ratio > 0.93:
            continue
        for bound, velocity in ((0.2, (-7, -6)), (0.35, (-5, -7)), (0.5, (-2, -8)),
                                (0.65, (2, -8)), (0.8, (5, -7)), (0.93, (7, -6))):
            if ratio <= bound:
                break
        hit = _tail_hit(grid, ball, x, paddle_y, velocity)
        if hit is not None:
            choices.append((hit['frames'], phase != scheduled, phase, mouse, hit))
    if not choices:
        return fallback
    _, _, phase, mouse, hit = min(choices)
    return dict(x=mouse, phase=phase, scheduled_phase=scheduled,
                policy='tail-ray', predicted_hit=hit)


def choose_mouse(state, step, lookahead=2):
    """Live ordinary-input policy, checked against original frame execution."""
    return choose_mouse_decision(state, step, lookahead)['x']
