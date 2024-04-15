### Browsing URLs

To browse URLs inside tmux you must have [urlview](https://aur.archlinux.org/packages/urlview/)AUR installed and configured.

Inside a new terminal:
```
bind-key u capture-pane \; save-buffer /tmp/tmux-buffer \; run-shell "$TERMINAL -e urlview /tmp/tmux-buffer"
```

Or inside a new tmux window (no new terminal needed):
```
bind-key u capture-pane \; save-buffer /tmp/tmux-buffer \; new-window -n "urlview" '$SHELL -c "urlview < /tmp/tmux-buffer"'
```

