"""Compatibility name for the contact policy used by campaign controls."""
from campaign_controller import choose_contact_mouse


def choose_earliest_contact(state, step):
    return choose_contact_mouse(state, step)
