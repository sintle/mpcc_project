#pragma once

#include "i18n/i18n.hpp"

Language get_i18n_zh_CN() {
	return Language {
		{"lang.name", "简体中文（中国）"},
		{"error.call.tooLessArgs", "需要提供至少 [Expected] 个参数，但是仅发现 [Current] 个。"},
		{"error.call.incorrectArgs", "需要提供 [Expected] 个参数，但是发现 [Current] 个。"},
		{"error.call.nativeFormat", "本地代码反馈了格式错误。"},
		{"error.call.nativeUnhandled", "本地代码反馈了未处理的错误。"},
		{"error.ast.program", "不兼容的格式！请检测该程序是否是为 MPCC Project 设计以及版本是否正确。"},
		{"error.evaluator.moreExpect", "希望捕获到 Array 型并用于参数展开，实际捕获到 [Type] 型。"},
		{"error.evaluator.constructorType", "构造函数必须是 Function 型。"},
		{"error.ast.functionInner", "Function 型的 Inner 属性必须为 Scope 表达式。"},
		{"error.call.notExecutable", "[Subject] 不是一个有效的函数或本地函数。"},
		{"error.call.notExecutable1", "不是一个有效的函数或本地函数。"},
		{"error.evaluator.nullAssignUnexpected", "预期之外的赋值到 Null 型变量。"},
		{"error.call.xcrementArgs", "Increment 函数或 Decrement 函数不能拥有参数。"},
		{"error.call.nativeFormat1", "[Subject] 包含的本地代码反馈了格式错误。"},
		{"error.call.nativeUnhandled1", "[Subject] 包含的的本地代码反馈了数据错误。"},
		{"error.call.indexArgs", "Index 函数必须包含正好一个参数且不得使用参数展开。"},
		{"error.index.stringAt", "String 型 Index 操作期望获得 [[Begin], [End]] 之间的下标，实际获得 [Index]。"},
		{"error.index.type", "Index 操作只接受 Integer 型或仅包含 Integer 型的 Array 型作为输入。"},
		{"error.index.incorrectRange.string", "对 String 型实施 Index 操作时遇到了宽度为负的区间：[[Start], [End]]。"},
		{"error.index.stringAt1", "String 型 Index 操作期望获得 [[Begin], [End]] 之间的下标，实际获得 [[I0], [I1]]。"},
		{"error.index.arrayAt", "Array 型 Index 操作期望获得 [[Begin], [End]] 之间的下标，实际获得 [Index]。"},
		{"error.index.incorrectRange.array", "对 Array 型实施 Index 操作时遇到了宽度为负的区间：[[Start], [End]]。"},
		{"error.index.arrayAt1", "Array 型 Index 操作期望获得 [[Begin], [End]] 之间的下标，实际获得 [[I0], [I1]]。"},
		{"error.index.typeSupport", "Index 操作只支持对 Array 型和 String 型使用。"},
		{"error.infix.notIdentifier", "成员必须通过 Identifier 表达式进行描述。"},
		{"error.infix.noSuchMember", "未找到该成员。"},
		{"error.infix.memberPrivate", "不能从外部访问类的私有成员。"},
		{"error.infix.noSuchEnumerate", "未找到该枚举值。"},
		{"error.call.prefixArgs", "Prefix 函数不能使用参数。"},
		{"error.stat.type", "Statement 表达式包含了预期之外的内容。"},
		{"error.value.type", "未知的值类型。"},
		{"error.statement.type", "未知的语句类型。"},
		{"error.call.infixArgs", "Infix 函数必须包含正好一个参数且不得使用参数展开。"},
		{"error.call.argData", "参数数据错误。"},
		{"error.unhandled", "未处理的错误在[Reason]"},
		{"error.program.init", "程序初始化错误。"},
		{"error.unexpected_node_type", "不期望得到的节点类型。"},
		{"error.argsize", "参数传递数量错误：[How]"},
		{"error.iconstructor", "不存在该构造函数。"},
		{"error.datatype", "数据类型错误：[How]"},
		{"error.datavalue", "不支持的数据值。"},
		{"error.notfound", "[Subject] 未找到"},
		{"error.moretype", "不兼容的参数展开器类型：[What]"},
		{"error.assignconstant", "正在尝试赋值一个常量：[What]"},
		{"error.assignBetweenTypes", "禁止将类型 [T1] 的变量赋值到类型 [T2] 的值。"},
		{"error.inherit", "不得继承尚不存在的类 [Name]。"},
		{"error.leveltype", "异常的<Instance>.__level__"},
		{"error.xcrementType", "不支持的 Increment/Decrement 作用类型。"},
		{"error.alreadyExists", "变量 [Name] 已经存在。"},
		{"error.forElement", "For 循环变量选择器错误：[How]"},
		{"error.xcrement", "Increment/Decrement 错误：[How]"},
		{"error.outOfRange", "超出范围：[What]"},
		{"error.invalid", "已弃用/不存在：[What]"},
		{"error.memberError", "寻找成员发生错误：[How]"},
		{"error.infix", "错误的 Infix [What] 作用在 [Left] 和 [Right] 之间。"},
		{"error.prefix", "错误的 Prefix [What] 作用在 [Type]。"}
	};
}