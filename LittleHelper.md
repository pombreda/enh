Little Helper is yet another application for quickly answering questions. Goals:

  * Be as simple as, or simpler than, Google's web search or Apple's Spotlight.
  * Be at least as fast as the competition.
  * Reduce the number of little tools
  * Be extensible, in any language of your choosing.

Ever since Google started with "onebox" (http://www.google.com/enterprise/gsa/onebox.html) and Apple's Spotlight added calculator functionality, I've wanted something similar for the Linux desktop. There are several contenders, but they're typical Linux apps, favoring power over simplicity. Deskbar (http://www.gnome.org/projects/deskbar-applet/) seems like the least worst, but it's got a more complicated UI than I'd like, and requires extensions be written in Python.

Microsoft's doing something sort-of similar (http://arstechnica.com/microsoft/news/2009/02/live-search-instant-answers-right-in-the-ie8-search-box.ars). And Google has a Mac-only Quick Search Bar (http://code.google.com/p/qsb-mac/).

See also Google's [Basic Search Help](http://www.google.com/support/websearch/bin/answer.py?answer=134479), [More Search Help](http://www.google.com/support/websearch/bin/answer.py?answer=136861), and [Search Extras](http://www.google.com/intl/en/help/features.html).

## Calculator ##

There's a simple calculator that supports:

  * Basic arithmetical operators (+, -, `*`, /).
  * Exponentiation (`^`).
  * Remainder (%).
  * Factorial (postfix !).
  * Bitwise operations (&, |, ~).
  * Logical not (prefix !).
  * Relational operators (==, !=, <, <=, >, >=).
  * Shifts (<<, >>).
  * Assignment (=).

Usual operator precedence ("order of operations") is followed, and parentheses are supported.

Numbers can be given in decimal (123), binary (0b1011), octal (0o777), and hex (0xfffe).

The constants e (2.718...) and pi (3.14...) are predefined.

There are also all the usual built-in functions:

  * abs.
  * acos, asin, atan, atan2, cos, cosh, hypot, sin, sinh, sqrt, tan, tanh.
  * cbrt, sqrt.
  * ceiling, floor, round.
  * is\_prime.
  * exp.
  * log(b, n), log10, log2, logE.
  * random.

The special variable Ans returns the result of the previous calculation.

## Unit Conversion ##

Simply say what you've got (123lbs, 5'4", 78F) and it will be automatically converted in to the appropriate unit (56kg, 1.62m, 26C). The input format takes into account what people actually write, assumes the obvious target unit, and retains the likely precision.

## Stuff To Do ##

  * "15mins check oven", "21:30 take pill" => set timers (for stuff not worth adding to a calendar).
  * currency conversions. see http://www.ecb.int/stats/exchange/eurofxref/html/index.en.html for data.
  * track parcels via tracking numbers.
  * installed applications. (annoyingly, Ubuntu has .desktop files for applications you haven't installed!)
  * contacts. (most useful somewhere with LDAP, since i don't keep my own address book.)
  * Maybe take into account that I'm a power user, and let me specify a verb?
    * "a gears of war", "i lord of war", "w gears of war", "gears of war" => amazon, imdb, wikipedia, and google searches.
    * "m 2 read", "j String" => man -s 2 read, latest javadoc for String
    * or Google-style "man:read(2)", "java:String", and so on. doesn't work well for things that are usually more than one word ("imdb:lord of war" would need extra quoting, for example, or maybe something like "imdb:" is a token in its own right that puts you in imdb mode for the rest of the tokens?).
    * leo.org translation? (what would be a convenient interface?)
    * dictionary/thesaurus? (plan 9 ones are good)
    * bug databases that i use? (my home projects, my work database, Sun's Java database...)
  * Some way to let people add their own stuff, without dictating an implementation language.
  * I'd rather write the core in Java than anything else; use gconf-editor and /apps/metacity/keybinding\_commands to get a global keyboard shortcut? What about Mac OS and Windows?