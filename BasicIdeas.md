(I don't think any of these ideas are particularly worthwhile. But if you're bored and looking for something to do...)

## C BBC Basic ##

A cross between C and BBC Basic.

Really not sure about missing out parentheses around `if` and `while` expressions, though it doesn't seem so bad on `for`.

Could probably get away with just string and double (and their arrays) to begin with. Just double if we're really just messing around. Not sure this could really go anywhere interesting anyway.

  * Types
    * Scalars:
      * `count%` - int32
      * `name$` - string
      * `average` - double
      * `done?` - bool
      * Maybe a byte type too, mainly so we can have byte arrays?
    * Vectors:
      * `counts%()` - vector`<`int32`>`
      * `names$()` - vector`<`string`>`
      * `averages()` - vector`<`double`>`
      * `dones?()` - vector`<`bool`>`

  * Literals
    * Numeric:
      * `0b1001` - binary
      * `0o777` - octal
      * `123` - decimal
      * `0xdeadbeef` - hex
      * `123.456` - real
    * Boolean:
      * `true`
      * `false`
    * String:
      * `"blah"`

  * Operators
    * Arithmetic:
      * `+`, `-`, `*`, `/`
      * `mod`, `rem`
    * Relational:
      * `<`, `<=`, `>`, `>=`
      * `==`, `!=`
    * Bit:
      * `and`, `or`, `xor`, `not`

  * Syntax
```
// if statements
if x == 0 {
 y = 0;
} else {
 y = a/x;
}

// while loops
while x > 0 {
 print(x);
 x = x - 1;
}

// for loops
for x = 0 to 9 { // end < start => step 1
 print(x);
}
for x = 9 to 0 { // end > start => step -1
 print(x);
}
for x = 0 to 20 step 4 {
 print(x);
}
for x = 20 to 0 step -4 {
 print(x);
}

// function
func strlen%(s$) {
 result% = 0;
 while s$ != "" {
  result% = result% + 1;
  s$ = drop$(s$);
 }
 return result%;
}

func abs%(i%) {
 if i% < 0 {
  i% = -i%;
 }
 return i%;
}

func abs(n) {
 if n < 0 {
  n = -n;
 }
 return n;
}

// procedure
proc error(msg$) {
 print(msg$);
 exit(1);
}

name$ = get$();
if strlen%(name$) > 4 {
 print("that's a long name!");
}

```

## ParaBasic/MetaBasic ##

An interpreter/compiler supporting everything traditional Basics did, but with a either a selection of front-ends or a parameterizable front-end, so you can run whatever kind of Basic program you happen to have. Something for those people who keep old software; let them unite around a single system rather than keep reinventing most of it. How practical is this? Would it get bogged down in bug-compatibility? Would it be better to have a translator from old dialects into One True (Clean) Dialect? (Quite possibly, though that might not be acceptable to the kind of person who might use this. And if you were going to translate, why not to a modern language?)