# How System Software Works: Introduction #

## What? Why? ##

"Reinventing the wheel" is a term always used negatively, but reinventing the wheel is exactly what someone ought to do if they're really interested in wheels. And there are so many parts to reinvent. We can go all the way down to how best to get ore from rock (assuming we even want metal wheels) or all the way up to the vehicles using wheels (assuming we even want vehicles with wheels). Although most people will never need to think too hard about wheels, there are people out there who think about wheels day-in, day-out, for a living.

Like wheels, there will probably always be system software. You can go lower, but not much lower before you hit hardware. You can go higher, but a lot of what you've learned will still be relevant, and you'll be better equipped to work on those higher layers if you have a firm understanding of what lies beneath.

But don't be misled. You probably aren't going to make a living writing assemblers, disassemblers, emulators/simulators, debuggers, VMs, compilers, linkers, or any of this stuff. There's a limit to how many of them the world really needs, and the limit's pretty low, and the jobs are already taken. So don't get too hung up on being a professional compiler writer, say, but take comfort from the fact that there's plenty of other software you can slip a lexer, parser, or even a language into.

This material is stuff I'd have loved to have read when I was starting out. I remember feeling cheated so many times by books that were missing half the code, or where the code, when I read it, didn't actually do as much as I'd been led to believe, or where some part of the system was so fake that it ruined the illusion. Even if you want to learn about assemblers, say, it's hard to get _too_ excited about an assembler for a made-up processor.

So I'll try to make things as realistic and complete as possible, and I'll point out where I'm cheating, and I'll point you in the direction of places you should go if you want more.

## Starting at the beginning ##

Like with the wheel example, above, there is no real beginning. Anyone who can program has come into contact with a compiler or interpreter. There's the runtime support below those, and the kernel supporting that, and the device drivers supporting that, and all this runs on a processor, and that processor's probably an x86 processor which is micro-coded, meaning that it's effectively got its own private language and the "machine instructions" you give it are actually broken down into micro-instructions, and those are implemented as logic gates and they're implemented with transistors and that's done on silicon wafers, and we're starting to get pretty close to pulling ore out of rock again.

You have to stop somewhere. For my purposes, I'll stop at the programmer's model of the processor. I'll talk about how a processor looks to the programmer, but I'll mostly ignore how the processor actually works.

## Prerequisites ##

If you can't program in any language, you need to learn one first. I'd recommend Java. Come back and have another go later.

If you don't know the basics of binary and hexadecimal arithmetic and logical operations, you need to learn them first. Come back and have another go later.

If you can't program in C++ or Java, you might need some other reference to help you understand all the code. For the most part, I'm only interested in talking about the higher-level techniques, not the specific syntax and library support.

If you don't know what assembly language is, you might find the stuff about assemblers, disassemblers, and emulators difficult until you do.