mp3d is for you if you have multiple computers but only one that has decent speakers. With mp3d running on that computer, the music comes out of the decent speaker no matter where the UI happens to be.

mp3d provides a web interface to your .mp3 collection, allowing you to search and queue tracks to be played. The tracks are played on the computer running mp3d. They are _not_ streamed to the computer you're running your web browser (many existing programs will do this if that's what you want).

FIXME: add a screenshot.

FIXME: add at least a Linux download so people don't have to build from source.

## Stuff To Do ##

  * Show how far through currently playing track we are. (XMLHttpRequest?)
  * Keep "currently playing track" updated. (XMLHttpRequest?)

  * Add play/pause icon.
  * Add "clear queue" icon/button.
  * Add rescan (preferably automatic).

  * id3v2 genre always seemed a bit over-precise and adding a table column for genre never struck me as a good idea, but it's probably worth at least distinguishing classical/non-classical (and music/spoken word, though i don't personally have any non-music). maybe a tabbed interface for this?

  * Improve German searching by normalizing umlauts to "ue" etc. (See http://www.allegro-c.de/papiere/umlaute.htm.)
  * Improve French/Italian searching by stripping accents.
  * Improve English sorting by ignoring leading articles ("a[n](n.md)|the").

  * Editing of id3v2 tags? Maybe as a separate desktop application to avoid security problems.

  * Feedback via the web interface while starting up, in case you have a huge collection.

  * .deb package. menu item to start server.