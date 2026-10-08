"""Mouse choices from observed gameplay state; no game-memory writes."""


CONTACT_BIASES = (0.08, -0.18, 0.30, -0.34, 0.16, -0.05)
DECISIONS_PER_CONTACT_BIAS = 100


def choose_mouse(state, step, lookahead=2):
    balls = state.get('balls') or []
    width = state['paddle_width']
    falling = [ball for ball in balls if ball['dy'] > 0 and not ball['attached']]
    ball = max(falling, key=lambda value: value['y']) if falling else (balls[0] if balls else None)
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
