"""Test-only mouse policy: ordinary falling balls and discrete wall projection."""
from campaign_controller import choose_mouse


def choose_earliest_contact(state, step):
    viable = [ball for ball in state.get('balls', ())
              if not ball['attached'] and ball['dy'] > 0 and ball['y'] + ball['dy'] <= 457]
    if not viable:
        retained = [ball for ball in state.get('balls', ()) if ball['attached'] or ball['dy'] <= 0]
        return choose_mouse(dict(state, balls=retained), step)
    def arrival(ball):
        distance = 450 - ball['height'] - ball['y']
        return max(1, (distance + ball['dy'] - 1) // ball['dy'])
    selected = min(viable, key=arrival)
    projected = dict(selected)
    x, dx = selected['x'], selected['dx']
    for _ in range(arrival(selected)):
        x += dx
        if x < 20:
            x, dx = 20, abs(dx)
        if x > 619 - selected['width']:
            x, dx = 619 - selected['width'], -abs(dx)
    projected.update(x=x, dx=0)
    return choose_mouse(dict(state, balls=[projected]), step, lookahead=0)
