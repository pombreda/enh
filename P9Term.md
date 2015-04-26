A reimplementation of Plan 9's terminal windows (described in [8½, the Plan 9 Window System](http://doc.cat-v.org/plan_9/4th_edition/papers/812/)), written in Java using PTextArea, looking like it belongs in the current decade rather than 1988.
  * how best to deal with tab completion?
  * command-line history?
  * color's probably quite easy; some visual distinction for stderr?
  * use control-c and so on for editing; esc for "interrupt".
  * getting Bash to behave?
  * any problems surrounding job control?
  * Plan 9-like "noscroll mode" where the default assumption is that you want to read command output, not watch it fly past.
If you want to play with it in its current state, I recommend:
```
  export PS1='% '
  stty -echo
```
I haven't done much work on this in some time. I think it's a good idea, despite the problems mentioned above (which mean it's unlikely to ever suit everyone, but that doesn't mean it wouldn't have its niche), but I don't actually use the shell any more than I have to these days, and [Terminator](http://software.jessies.org/terminator/) is pretty good.

See also [9term](http://swtch.com/plan9port/man/man1/9term.html).