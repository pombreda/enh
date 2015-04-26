(This is not a complete list. Only projects that had some amount of effort put into them and might usefully be resurrected are described here.)

## Mailer ##

In  `graveyard/mailer/`. From what was to have been the documentation:

**Mailer is a cross-platform GPL desktop mail client designed to be fast and simple.**

Mailer is compatible with IMAP incoming mail servers and SMTP outgoing mail servers.
It replaces Outlook, Evolution, and Apple's Mail.app.

Mailer was designed as a no-nonsense mail client after too many years fighting over-clever, over-configurable mailers on various platforms. Almost every mailer has something it does really well, but every mailer has some fundamental problem (even if it's only the lack of spelling checking as you type, or being tied to one particular platform):

  * **Available Everywhere** - Mailer runs on Linux, Mac OS, Solaris, and Windows. No more using a different mailer on every platform.

  * **Strong Plain-Text Editing** - Mailer uses an industrial-strength custom text component for displaying/editing plain text. (The same component is used in the full-blown editor for programmers, [Evergreen](http://software.jessies.org/evergreen/).)

  * **Designed For Keyboard Navigation** - Sometimes you're using the mouse, and sometimes you're using the keyboard. Apple's Mail.app showed how the flow in a GUI mailer could be improved by strong keyboard support, and Mailer is designed to be at least as good. In particular, when the mailbox table has the focus, the up and down arrow keys change the selected message, but the page up/page down and home/end keys scroll through the body of the currently selected message rather than much less usefully scrolling the table itself. The delete key moves selected messages to your trash folder, and shift-delete permanently deletes selected messages, bypassing the trash folder as in Outlook.

  * **Designed For High-Latency Links/Slow Servers** - Not everyone is on the same LAN as their IMAP server, but many mailers behave as if they were. Mailer tries not to waste your time with unnecessary network ping-pong matches.

  * **Secure** - Use SSL to connect to your IMAP and SMTP servers, and use SMTP authentication to identify yourself to your outgoing mail server. Your IMAP and SMTP passwords are not stored on disk.

  * **Simple Delete Behavior** - Deleting a mail moves it to the trash folder; permanent deletion marks the message as deleted. Both expunge immediately. This is much less confusing if you point multiple mailers (or multiple instances of the same mailer) at the same mail store, because you don't log out at work when you go home, say, or because you have multiple computers around the house. Some argue that IMAP's existing distinction between marking as deleted and expunging is the appropriate implementation of two-stage deletion, but unless all clients agree on it, it causes trouble. It also means that your most frequently-accessed folder, your inbox, is larger than under the "move to trash" scheme.

  * **No POP** - IMAP offers the potential for better performance, better functionality, and better concurrent behavior than POP did. Only supporting IMAP also simplifies configuration.