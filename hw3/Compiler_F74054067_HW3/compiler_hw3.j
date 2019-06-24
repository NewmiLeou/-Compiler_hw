.class public compiler_hw3
.super java/lang/Object
.method public static main([Ljava/lang/String;)V
.limit stack 50
.limit locals 50
	ldc 20
	istore 0
	iload 0
	ldc 40
	isub
	ifeq LABEL1_1_1
	goto END1_1_1
LABEL1_1_1:
	ldc "a is equal to 40"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
	goto EXIT1_1
END1_1_1:
	iload 0
	ldc 40
	isub
	ifgt LABEL1_1_2
	goto END1_1_2
LABEL1_1_2:
	ldc "a is larger than 40"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
	goto  EXIT1_1
END1_1_2:
	ldc 666
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
EXIT1_1:
	return
.end method
