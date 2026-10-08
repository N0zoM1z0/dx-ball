"""Mouse choices from observed gameplay state; no game-memory writes."""


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


def choose_mouse(state, step, lookahead=2):
    """Live ordinary-input policy, checked against original frame execution."""
    return choose_contact_mouse(state, step, lookahead)
