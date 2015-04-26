#### How do I get Dalvik Explorer? ####
If you just want to use Dalvik Explorer, you can find it in the Market on your phone. Search for "Dalvik Explorer" (<a href='market://details?id=org.jessies.dalvikexplorer'>direct link</a>).

It's a free download. Old versions (and the current version if you don't have Market access) are [available here](http://code.google.com/p/enh/downloads/list).

#### How do I report a bug/provide general feedback? ####
Click on the "Issues" tab above and then click on "New issue". Or follow this direct link: [report a bug](http://code.google.com/p/enh/issues/entry).

If you want to give me feedback that you don't think counts as an "issue", feel free to use the "Mail author" facility in the Market on your phone instead.

#### Where's the source code? ####
If you came here for the source code, click on the "Source" tab above and follow the instructions.

#### Future Enhancements ####

The file system viewer should show information equivalent to "ls -l". Also MIME type. Also menu option to send ACTION\_VIEW intent before viewing as text in built-in FileViewerActivity. (Maybe automatic, based on guessed MIME type?)

Add a character viewer? So you'd type 202a or whatever and get to see U+202a, plus maybe the result of all the methods in Character applied to that code point?

Don't even try to view files that are > 1/2 our heap size? hexdump view?

Write summary to sd card rather than trying to mail (since the summary is so large, mail tends to choke)?

Built-in benchmarks?

Network interfaces?

Crypto stuff?

#### What changed between versions? ####

| **Version** | **Details** |
|:------------|:------------|
| 3.9 | Don't start a service for the widget. |
| 3.8 | Theme refresh. isLowRamDevice. |
| 3.7 | Fast scrolling and filtering by subtitle. Bug fix for CPU speeds >= 2GHz. Fixed first day of week and currency symbol display. Sensors. |
| 3.6 | Make widget text fit better. Added version number to title. |
| 3.5 | Added build widget. Started using HTML formatting. Show timeFormat12 and timeFormat24 in LocaleData. |
| 3.4 | Get exact screen resolutions (on Android releases with a system bar). |
| 3.3 | Work around a Currency.getInstance bug. Really fix file system info pre-Gingerbread. |
| 3.2 | Decode Qualcomm part numbers. Save/restore list filter and scroll position. Clearer output for time zones that have never had a transition. |
| 3.1 | Only show stand-alone days/months where they differ. Fix CPU frequency units. Fix file system info pre-Gingerbread. |
| 3.0 | Time zone transitions. CPU frequencies. Fix processor identification on x86. |
| 2.9 | More locale data post-Gingerbread. /proc/meminfo summary in Device Details. Mount point details. |
| 2.8 | Maps links from time zones. MIPS support. Currency details. |
| 2.7 | Fixed core count on all builds. Split build and device details, and added more processor details to the latter. |
| 2.6 | Fixed core count on old builds. |
| 2.5 | More build/device details, GoogleTV support. |
| 2.4 | More time zone information, track system default time zone changes while running. |
| 2.3 | Include charset aliases, and summarize time zone information. |
| 2.2 | Better Honeycomb support. More obvious search in text views/filtering in lists. Also show display names for locales in lists. |
| 2.1 | Show tzdata version. Describe the display in Build/Device Details. Show locale display names in the locale itself as well as the device's default locale. Substring rather than prefix filtering in lists. |
| 2.0 | Show Runtime.availableProcessors() in Build/Device Details. |
| 1.9 | Fix the shortcut to the default locale. Better support for large screens. |
| 1.8 | Use a two-level locale hierarchy, grouping locales by language. |
| 1.7 | All text views copyable & mailable. File system browser can now send ACTION\_VIEW intents. First day of week/minimal first days in week. |
| 1.6 | Filterable lists. VM heap size in device info. |
| 1.5 | Fix build/device info for pre-Android 1.6 devices. |
| 1.4 | Build/device info, file system browser, options menu (mail report, help). |
| 1.3 | Full details of date/time/number formatting (per locale). |
| 1.2 | More detailed information on charsets, locales, and time zones. |
| 1.1 | Split the output into sections. |
| 1.0 | Initial release. One big text view. |