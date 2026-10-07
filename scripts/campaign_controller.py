"""Mouse choices from observed gameplay state; no game-memory writes."""


def choose_mouse(state, step, lookahead=2):
    balls = state.get('balls') or []
    width = state['paddle_width']
    falling = [ball for ball in balls if ball['dy'] > 0 and not ball['attached']]
    ball = max(falling, key=lambda value: value['y']) if falling else (balls[0] if balls else None)
    center = state['paddle_x']
    urgent = ball is not None and ball['dy'] > 0 and ball['y'] > 390
    if ball is not None:
        center = ball['x'] + ball['width'] / 2 + ball['dx'] * lookahead
    bias = width * 0.2 * (-1 if (step // 100) % 2 else 1)
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
