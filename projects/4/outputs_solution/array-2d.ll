; ModuleID = 'outputs/array-2d.ll'
source_filename = "outputs/array-2d.ll"

%Array2D = type { [3 x [4 x i32]] }

@Array2D.global = global %Array2D zeroinitializer
@printf.format = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(...)

define i32 @main() {
entry:
  %j = alloca i32, align 4
  store i32 0, i32* %j, align 4
  %i = alloca i32, align 4
  store i32 0, i32* %i, align 4
  br label %loopcond

loopcond:                                         ; preds = %loopend3, %entry
  %0 = load i32, i32* %i, align 4
  %1 = icmp slt i32 %0, 3
  br i1 %1, label %loopbody, label %loopend

loopbody:                                         ; preds = %loopcond
  store i32 0, i32* %j, align 4
  br label %loopcond1

loopend:                                          ; preds = %loopcond
  store i32 0, i32* %i, align 4
  br label %loopcond5

loopcond1:                                        ; preds = %loopbody2, %loopbody
  %2 = load i32, i32* %j, align 4
  %3 = icmp slt i32 %2, 4
  br i1 %3, label %loopbody2, label %loopend3

loopbody2:                                        ; preds = %loopcond1
  %4 = load i32, i32* %i, align 4
  %array.element = getelementptr inbounds [3 x [4 x i32]], [3 x [4 x i32]]* getelementptr inbounds (%Array2D, %Array2D* @Array2D.global, i32 0, i32 0), i32 0, i32 %4
  %5 = load i32, i32* %j, align 4
  %array.element4 = getelementptr inbounds [4 x i32], [4 x i32]* %array.element, i32 0, i32 %5
  %6 = load i32, i32* %i, align 4
  %7 = mul i32 %6, 4
  %8 = load i32, i32* %j, align 4
  %9 = add i32 %7, %8
  store i32 %9, i32* %array.element4, align 4
  %10 = load i32, i32* %j, align 4
  %11 = add i32 %10, 1
  store i32 %11, i32* %j, align 4
  br label %loopcond1

loopend3:                                         ; preds = %loopcond1
  %12 = load i32, i32* %i, align 4
  %13 = add i32 %12, 1
  store i32 %13, i32* %i, align 4
  br label %loopcond

loopcond5:                                        ; preds = %loopend10, %loopend
  %14 = load i32, i32* %i, align 4
  %15 = icmp slt i32 %14, 3
  br i1 %15, label %loopbody6, label %loopend7

loopbody6:                                        ; preds = %loopcond5
  store i32 0, i32* %j, align 4
  br label %loopcond8

loopend7:                                         ; preds = %loopcond5
  ret i32 0

loopcond8:                                        ; preds = %loopbody9, %loopbody6
  %16 = load i32, i32* %j, align 4
  %17 = icmp slt i32 %16, 4
  br i1 %17, label %loopbody9, label %loopend10

loopbody9:                                        ; preds = %loopcond8
  %18 = load i32, i32* %i, align 4
  %array.element11 = getelementptr inbounds [3 x [4 x i32]], [3 x [4 x i32]]* getelementptr inbounds (%Array2D, %Array2D* @Array2D.global, i32 0, i32 0), i32 0, i32 %18
  %19 = load i32, i32* %j, align 4
  %array.element12 = getelementptr inbounds [4 x i32], [4 x i32]* %array.element11, i32 0, i32 %19
  %20 = load i32, i32* %array.element12, align 4
  %21 = call i32 (...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf.format, i32 0, i32 0), i32 %20)
  %22 = load i32, i32* %j, align 4
  %23 = add i32 %22, 1
  store i32 %23, i32* %j, align 4
  br label %loopcond8

loopend10:                                        ; preds = %loopcond8
  %24 = load i32, i32* %i, align 4
  %25 = add i32 %24, 1
  store i32 %25, i32* %i, align 4
  br label %loopcond5
}
