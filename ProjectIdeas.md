(If you decide to implement any of these ideas yourself, or if you think you've already written something that's a pretty good fit, please send me a link. I'd like nothing more than to not have to write and maintain these myself!)

## A better UI for building/testing ##

Break the UI for building/testing out of the IDE. It shouldn't be specific to any given IDE (and should even work for command-line Emacs/Vim users), nor specific to any given build/test tool. Who cares if you're using GNU Make or Ant or whatever. The principles rarely differ much (though some may offer richer output than others). Recognize progress indications and show them as such. Recognize errors and warnings and color them, collect them, and link them back to editors (okay, I'll be honest; I only really care about using Evergreen as my editor, so I'm not much deterred if it's not possible/convenient to link back to other editors).

Auto-complete targets for those build tools that offer target query interfaces. History of recently-built targets/other options. Preset "debug" and "release" option sets. Acme/Oberon-like way to trivially (and textually) make your own buttons corresponding to particular build/test run "configurations" (the combination of options and targets).

Some RPC mechanism so that an IDE's built-in "build" and "test" functions can call out to rerun the last build/test configuration, rather than forcing the user to hunt out the window and press the right button.

Here's the [Newspeak test results UI](http://gbracha.blogspot.com/2009/02/newspeak-prototype-escapes-into-wild.html), which doesn't look particularly convincing, but is at least colorful.

## A to-do app that doesn't suck? ##

I've tried several to-do apps, plain text, wiki pages, bug databases, and paper, and I'm still not happy. Is "happy" possible? (The guy wrote wrote http://shawnblanc.net/2009/01/a-review-of-two-things/ seems happy.)

Alternatively, one could just use a "notes" app. http://daringfireball.net/2009/07/simplenote is a review of one.

## code.google.com wiki markup translators ##

I've already got a Talc script to convert man pages to code.google.com wiki markup, and [blog-baboon](http://code.google.com/p/blog-baboon/) uses a subset of the same markup, but how about:
  * Converting to/from LaTeX (for printing)?
  * Converting to/from HTML (so this same markup can be used independently of code.google.com)? (See [blog-baboon](http://code.google.com/p/blog-baboon/) for a subset.)

## Log viewer ##

Chris Reece wondered about hacking [Terminator](http://software.jessies.org/terminator/) to be a log viewer. Apple has Console.app. GNOME has System Log Viewer. I tend to use "tail -F" in Terminator. Random ideas:
  * Could cope with .gz logs (unlike GNOME).
  * Could transparently stitch rotated logs together.
  * Could divide into days (like GNOME, which even shows a calendar).
  * Could filter (like Console.app).
  * Usual "jessies" find.
  * Could show as table (like Console.app in 10.5), or wrap (like XTerm), or scroll horizontally (like Terminator or GNOME).
  * Vim does simple coloring of some log formats.
  * Could gray out in each line every character (or run of a certain length?) that's the same as the previous line.
  * Could toFront/flash on new output.
  * Could offer setAlwaysOnTop.
  * "tail -F"-like automatic following of rotated logs.
  * If process _pid_ dies, automatically show me log _path_. Perhaps handier for developers than sys admins, but meant for anyone who's expecting a daemon to die and wants its death brought to their attention (and knows the first thing they'll do is look at the [crash](crash.md) log).

## System monitor ##

I love things like Apple's "Activity Monitor", GNOME's "System Monitor", and whatever the sysinternals' guy's thing for Windows is called, but none of them is really perfect.

Basic info:
  * icon (how?), name, pid, status, % CPU, "memory" (which one/s?), user (?)
    * tty is useful for distinguishing bash(1) instances.
    * arguments are often useful; include them (truncated) in name, and rely on tool tips, or show them as part of a process' detailed info?
    * GNOME System Monitor has "X Server Memory" which sounds interesting.

On a process:
  * show open file descriptors: number, type, details
    * file & filename
    * pipe & process (by matching the magic number in the other process' fds)
    * network socket and endpoint (magic numbers mapped somewhere in /proc/net)
  * show environment variables
  * show cwd and root
  * show memory map
  * send signal (at least stop, continue, and kill)
  * show parent name and pid; clickable.
  * strace(1), ltrace(1).
    * "strace -C" is often instructive enough.
    * important to be able to stop tracing quickly and easily.
    * could use strace(1) to monitor an application's pipe/network communication.
  * turn GNU profiling stuff on/off in a binary with symbols to offer something like Apple's sample(1).

On a process' binary:
  * strings(1), nm(1), ldd(1).

On a Java process:
  * jstack(1), jmap(1), jinfo(1).
  * injection of arbitrary agents into Java 6 processes.
    * default set of agents to replace our current "Debug" menu.
    * plus stuff like tracing and profiling that's hard to do in-process.
    * watching the AWT event queue would often be interesting.

Main table options:
  * show all/active/mine.
  * indentation showing process hierarchy.
  * sortable columns (should be true of all tables in the application).
  * search for processes with a particular file open or socket endpoint.

Per-process detail windows:
  * also update, but have "pause"?
  * don't disappear if/when process exits (but clearly say "Terminated").

top(1)-like overall info:
  * % user, system, nice, idle?
  * thread/process/runnable counts?
  * memory, disk usage, disk activity, network activity?

Update frequency/period:
  * integer text field, or "very often (0.5 s)", "often (1 s)", "normal (2 s)", "less often (5 s)" like Activity Monitor?
  * or always update the tray icon but have a play/pause button in the main window? lets you watch stuff as it changes, but then stop things jumping about when you actually decide you've found something you want to look at. (can't, of course, ensure that all the processes frozen on the display are still there or in their interesting state when you ask further questions about them!)

Tray icon:
  * image shows CPU usage graph.
  * tool tip shows name and pid of process using most CPU.
  * click opens main window.
  * GNOME's tool's network and disk (i/o rather than space) monitors are useful, and the memory monitor's somewhat useful (though not useful enough to be worth as much horizontal space as the others).

## How (Software) Stuff Works ##

A tour (with minimalist implementations) of the basic bits of software:
  * ARM emulator (to give an overview of how a nice processor works).
  * ARM assembler/disassembler.
  * BASIC interpreter (or compiler, or both?). (See also BasicIdeas.)
  * higher-level VM?
  * a Unix shell?
  * anything else interesting enough? (should be non-trivial yet practical.)
  * what implementation language? C++ or Java?

## Hack on Maxine ##

Sun's [maxine](https://maxine.dev.java.net/) JVM looks mildly interesting.
  * Linux support?
  * ARM support?
  * see what else comes to mind if/when i can actually run it ;-)

## v8jam ##

Any benefit to using the [v8](http://code.google.com/p/v8) GC in jam? How about the JIT? Jam starts up very fast, and is fast as interpreters go, but it's seriously slow compared to HotSpot/GCJ generated code.

## Android on Linux ##

Might be interesting to be able to run Android stuff native on Linux. Either by porting the GUI stuff and sticking with DalvikVM, or porting the Android stuff to Sun's JVM/Java2D and so forth.

How to build/run DalvikVM on Linux/x86:
http://groups.google.com/group/android-porting/browse_thread/thread/ab553116dbc960da/db0e127f7f8db0da