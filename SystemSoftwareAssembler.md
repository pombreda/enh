# How System Software Works: Assembler #

When you compile a program, it's translated from a high-level language meant for humans into a lower-level language meant for machines. Some compilers compile straight to binary files containing machine code -- or bytecode, as with `javac(1)` -- but others, especially older ones, compile to assembly language, a textual form of machine code.

You can ask most compilers to output assembly language, even if they normally wouldn't, usually by adding the `-S` flag to the command line. Typically, the output will be a `.s` file (instead of the usual `.o` or `a.out`). Let's take this minimal C++ program as an example:

```
$ cat ex.cpp 
int main() {
  return 0;
}
```

If we ask the compiler to output assembly language and look at the output, we see this:

```
$ g++ -S ex.cpp 
$ cat ex.s 
	.file	"ex.cpp"
	.text
	.align 2
.globl main
	.type	main, @function
main:
.LFB2:
	pushq	%rbp
.LCFI0:
	movq	%rsp, %rbp
.LCFI1:
	movl	$0, %eax
	leave
	ret
.LFE2:
	.size	main, .-main
.globl __gxx_personality_v0
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0x0
	.byte	0x1
	.string	"zPR"
	.uleb128 0x1
	.sleb128 -8
	.byte	0x10
	.uleb128 0x6
	.byte	0x3
	.long	__gxx_personality_v0
	.byte	0x3
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 8
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.long	.LFB2
	.long	.LFE2-.LFB2
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI0-.LFB2
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE1:
	.ident	"GCC: (GNU) 4.2.3 (Ubuntu 4.2.3-2ubuntu7)"
	.section	.note.GNU-stack,"",@progbits
```

Before you get too scared and run away, the interesting part is just this:
```
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$0, %eax
	leave
	ret
```

And the only necessary "active ingredients" there are just:
```
	movl	$0, %eax
	ret
```

Even if you don't know assembler, you can probably guess that's just "move 0 into something called %eax, and return".

As an aside, if you ran `g++ -O2` rather than just `g++` as I did above, you'll actually get this output. Although you might imagine that compilers' optimizations will be too complex for you to follow -- because optimized high-level code tends to be harder to follow -- it's often the case that optimized assembler is easier to read. Compilers often output very stupid code by default, knowing that their later optimization passes will clean it up. So in the original unoptimized example you had to wade through a default function prolog and epilog (which we'll look at later) to see the two instructions that actually do anything.

**EXERCISE** Try this on your own computer. If you don't have an x86 processor, your output is likely to be very different, but see if you can work out which is the bit that does the actual work. (As a hint, there will likely be the word "main" nearby.) If you're not running Linux and using GCC, the commands and flags you need might be different.

**EXERCISE** Try different optimization levels and check that what I said above is true. On my system, if I use `-O3`, I get the same number of instructions, but the `movl` is replaced by `xorl %eax, %eax`. Find out why. (As a hint, compiling with `-c` to generate `ex.o` and the looking at the output of `objdump -d ex.o` will be helpful.)

## What's an assembler? ##

An assembler translates an assembly language into machine code, a binary representation of the instructions the processor understands. For example, our minimal C++ program ends up on x86 as the following six bytes of machine code instructions:

```
b8 00 00 00 00       	movl    $0,%eax
c3                   	retq   
```

The right-hand column shows the instructions, and the hex numbers in the left-hand column are the bytes they correspond to. You'll notice that the instructions are of different lengths. The `retq` instruction takes up just a single byte, 0xc3, where the `movl` instruction consists of a single-byte "opcode", 0xb8, corresponding to `movl` and four zero bytes corresponding to the 32-bit number 0. (The `l` in `movl` stands for "long", which in the x86 world means 32 bits.)

This leads us to the answer to the question of why the compiler might output `xorl` instead of `movl`:

```
31 c0                	xorl    %eax,%eax
```

Here we see that the `xorl` instruction is only two bytes long, because there's no need for the 32-bit constant. The instruction exclusive-ors the register with itself, with the effect that zero bits stay zero and one bits get cleared, since 1 exclusive-ored with 1 is 0. The effect is the same, but the code is shorter. This definitely means you can fit more code in the processor's instruction cache, and may mean that the code runs faster, though realistically you don't know what the micro-instructions the processor actually translates the `movl` to.

Anyway, what's the difference between an assembler and a compiler? They sound pretty similar because they are pretty similar. The major difference is just that the input language to an assembler is quite a lot simpler than the usual input languages to compilers. But really, an assembler is a simple special case of a compiler.

## What do assembly language programs look like? ##

Different processor families, such as the x86 processors used in Macs and PCs, the ARM processors used in iPods and smart phones, the PowerPC processors used in the Xbox 360, and so on, have their own assembly languages. The instructions are different. But the overall format of the assembler's _input_ is pretty similar.

Going back to a snippet of our example:

```
	.file	"ex.cpp"
	.text
	.align 2
.globl main
	.type	main, @function
main:
.LFB2:
	pushq	%rbp
.LCFI0:
	movq	%rsp, %rbp
.LCFI1:
	movl	$0, %eax
	leave
	ret
.LFE2:
```

The `.file`, `.text`, `.align`, `.globl`, and `.type` lines are called directives. These are instructions to the assembler itself.

The `main:`, `.LFB2:`, `.LCFI0:`, `.LCFI1:`, and `.LFE2:` lines are called labels. These are names for locations that can be used for jumps, loads, stores, or even arithmetic. The `.LFB2` and `.LFE2` labels, for example, obviously mark the Begin and End of the Function. Later on in the full output you can see that `.LFE2 - .LFB2` is stored in the output, so something obviously wants to know the size of the function.

The other lines, like `movl $0, %eax` and `ret`, are called instructions.

Instructions can be further broken down into mnemonics (such as `movl` and `ret`) and arguments (such `$0, %eax`).

## Different processors ##

Today (and for at least the past decade) the dominant processor architecture is the x86 architecture. This corresponds to a large number of actual processors, from the 8086 that's about my age to the Core 2 Quad I'm using right now. There are other unrelated families, as mentioned earlier. Until recently Apple desktops and laptops used the PowerPC family, and before that they used the 68000 family, and before that they used the 6800 family. iPods and iPhones and many other devices that need processors that don't consume much power tend to use the ARM family.

### CISC versus RISC ###

The biggest difference between the dominant x86 family and the ARM family (which I'm going to concentrate on) is that the x86 processors are CISC and the ARM processors are RISC. A long time ago, people building processors thought that adding more complex instructions, that better matched the high-level languages, was the best way to achieve performance. These were the Complex Instruction Set Computers, and they had a lot of instructions, a lot of irregularity amongst those instructions, and some instructions that did some very complicated things.

Other people came along and said, no, the way to achieve performance is to have simpler processors. Because these came later, these were the Reduced Instruction Set Computers, and they had fewer instructions, more regularity amongst their instructions, and most instructions were very simple.

(Mention good architecture books.)

For the most part, "CISC won", though, as in any case of "survival of the fittest", you shouldn't read too much into what their current dominance means. As for the RISC processors, the Xbox 360 uses the RISC PowerPC, and the RISC ARM thrives everywhere power consumption is important. One side-effect of being simple is that you can do more with less, and sometimes that's important.

I'm going to focus on the ARM because I'm familiar with it, it's a realistic processor that's still in use, and it's simple. This simplicity means I can show you a realistic assembler, disassembler, and emulator for the ARM without taking up too much space and without getting too bogged down in trivial details. (I will reproduce a few of the ARM's uglier characteristics, though, for the sake of realism, and as a reminder that nothing's perfect.)

(Come back to how higher-level code looks in assembler, or digress here?)

## The ARM processor ##

(Basics. Only ARMv2. Only user-mode stuff, but mention the missing bits.)

## The tools ##

(No good order to these. All three are interrelated and it helps to develop all three in parallel. But we have to show them in some order, so...)

## A disassembler ##

(Similarity to processor's decoding logic. Benefits of regularity and orthogonality and fixed-size instructions.)

## An assembler ##



## An emulator ##

(Difference between emulator and simulator.)