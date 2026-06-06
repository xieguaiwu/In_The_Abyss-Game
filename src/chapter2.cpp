#include "platform.h"
#include "common_vars.h"
#include "functions.h"
#include "print.h"
#include "story.h"
#include "game_state.h"

// ============================================================
// 第二章：办公室与楼梯间
// ============================================================

void a2_2() {
	const int floor = 30;
	int jump = 0;

	text("附着在尘埃里，喀戎", 1);
	text("藏隐在尘埃里，喀戎");
	text("摘下尘埃的面具，极乐");
	text("口琴内含着万里尘埃，犬吠");
	text("加速！加速——");
	text("-阴凉的尘埃-", 1);
	text("一无所有，");
	text("一无所有！", 1);
	light();
	text("走进楼梯间，橙黄的光创造世界的另一个独属于阴影的空间");
	text("在朦胧中瞌着眼，你的世界随阳光透过的毛细血管变得一片血红");
	text("疲劳从双眼升腾……阴影自身后凸现；阳光透过骨骼透过疲倦透过半透明的倾斜的地轴");
	text("-要下楼梯了……-");
	while (1) {
		if (floor > jump) std::cout << "还剩" << floor - jump << "（/" << floor << "）层\n";
		else break;
		puts("A.走一层楼梯");
		puts("B.一次性跳下两层楼梯");
		puts("C.一次性跳下三层楼梯");
		puts("D.一次性跳下四层楼梯");
		puts("E.一次性跳下五层楼梯（只剩下五层楼梯时必定成功；其他之后较小概率判定成功——不成功便成仁）");
		key = getch();
		if (key == 'A' || key == 'a') {
			text("你走下了一层楼梯", 1); jump = jump + 1;
		}
		else if (key == 'B' || key == 'b') {
			if (jump >= floor / 2) {
				text("你跳下了两层楼梯");
				text("-你实在感到棒极了-", 1);
				jump = jump + 2;
			}
			else {
				random_val = r(0, 11);
				if (random_val == 9) {
					text("【判定失败】！你滚下了楼梯……", 1); jump = floor;
				}
				else {
					text("【判定成功】！你一次性跳下了两层楼梯！", 1); jump = jump + 2;
				}
			}
		}
		else if (key == 'C' || key == 'c') {
			if (floor - jump == 3 || floor - jump == 4) {
				text("你跳下了三层楼梯");
				text("-你平稳落地-", 1);
				jump = jump + 3;
			}
			else if (jump >= floor / 3) {
				random_val = r(0, 11);
				if (random_val == 9) {
					text("【判定失败】！你滚下了楼梯……", 1); jump = floor;
				}
				else {
					text("【判定成功】！你一次性跳下了三层楼梯！", 1); jump = jump + 3;
				}
			}
			else {
				random_val = r(0, 6);
				if (random_val == 5) {
					text("【判定失败】！你滚下了楼梯……", 1); jump = floor;
				}
				else {
					text("【判定成功】！你一次性跳下了三层楼梯！", 1); jump = jump + 3;
				}
			}
		}
		else if (key == 'D' || key == 'd') {
			if (floor - jump == 4) {
				text("你跳下了四层楼梯");
				text("-你平稳落地-", 1);
				jump = jump + 4;
			}
			else {
				random_val = r(0, 3);
				if (random_val == 1) {
					text("【判定成功】！你一次性跳下了四层楼梯！", 1); jump = jump + 4;
				}
				else {
					text("【判定失败】！你滚下了楼梯……", 1); jump = floor;
				}
			}
		}
		else if (key == 'E' || key == 'e') {
			if (floor - jump == 5) {
				text("你跳下了五层楼梯");
				text("-你平稳落地-", 1);
				jump = jump + 5;
			}
			else {
				random_val = r(0, 5);
				if (random_val == 1) {
					text("【判定成功】！你一次性跳下了五层楼梯！");
					text("-你感觉自己到达了人生的巅峰-", 1);
					jump = jump + 5;
				}
				else {
					text("【判定失败】！你滚下了楼梯……", 1); jump = floor;
				}
			}
		}
	}
	text("你离开了写字楼……");
	text("……", 1);
	a3();
}

void a2_1() {
	text("继续工作，你开始制作表格，而后写起了报告……", 1);
	text("花费几十分钟完成了第一篇报告，你要");
	puts("A.提交给上司");
	puts("B.偷偷写“肥猪高速公路”（不会有人知道这是什么意思的）然后提交给上司");
	puts("C.丢尽废纸篓并彻底粉碎");
	while (1) {
		key = getch();
		if (key == 'A' || key == 'a') {
			text("你把文件交给部门经理，后者决定为你增加工作量"); break;
		}
		else if (key == 'B' || key == 'b') {
			if (!GameState::instance().check_flag("shame")) {
				text("上司接受了报告，你庆幸他并没有看出端倪");
			}
			else {
				text("不久后，部门经理摆着一副臭脸从办公室里走出");
				text("【部门经理】你到底想要干什么？先是恬不知耻地在办公室里脱内裤又突然仿佛就要哭了一样，然后又是这个！");
				text("【部门经理】别让我再看到你发疯的样子，要不然你也不用来见我了！");
				text("你的上司又怒气冲冲地回到了办公室里。你希望乘坐肥猪高速公路的末班车离开这栋写字楼。");
				text("解锁成就【肥猪高速公路】！"); GameState::instance().visit("achievements");
			}
			break;
		}
		else if (key == 'C' || key == 'c') {
			text("-“聪明，这样便可以拖延时间减少工作量”-");
			text("你如此做了，然后又打印出了一份报告交给上司");
			break;
		}
	}
	text("接下来是一系列文件");
	puts("先做哪个？");
	puts("A.待批注的法律文书");
	puts("B.待制定参会人员公司内部报告会（为什么你总是有如此多助理任务？）");
	puts("C.帮部门经理秘书制定秘书时间表（这是什么东西？）");
	puts("D.攻克函数库的一项难题");
	puts("E.又是待批注的法律文书");
	while (1) {
		key = getch();
		if (key == 'A' || key == 'a') {
			text("你批注了那些自己一窍不通的法律文书");
			text("-这是法务部的文件，你拿错文件了！-");
			text("你尴尬地把它放回文件箱里，假装一切都好");
			break;
		}
		else if (key == 'B' || key == 'b') {
			text("你要到了部门员工的工作时间表，将内部报告会的时间与同事的假期时间与级别相互对照");
			text("-有史以来最无聊的工作诞生了-");
			break;
		}
		else if (key == 'C' || key == 'c') {
			text("你打电话给经理秘书询问这项奇怪的工作");
			text("【部门经理秘书秘书】您好，有什么能帮您的吗？");
			text("……");
			text("【部门经理秘书秘书】你的请求现已被移交给我的秘书，希望她能帮助你");
			text("……");
			text("【部门经理秘书秘书秘书】已阅！");
			text("……");
			text("在等待进一步提示时，你已经做好了时间表。再看看话筒，你发现对方早已挂断……");
			break;
		}
		else if (key == 'D' || key == 'd') {
			text("你使用权限查看了报告文件，然后打开了源代码");
			text("在看到程序作者的一瞬间，你感到心跳加速——那居然是齂怪物的手笔，时间一切鼎鼎大名的垃圾代码的作者！");
			text("你决定丢下这项工作……");
			break;
		}
		else if (key == 'E' || key == 'e') {
			text("你批注了那些自己一窍不通的法律文书");
			text("-这是法务部的文件，你拿错文件了！-");
			text("你尴尬地把它放回文件箱里，假装一切都好");
			break;
		}
	}
	text("头疼了一整天，你去吃了午餐");
	text("-不小心呛了一口楼梯间的尘埃，你几乎犯了哮喘-");
	puts("（按【Z键】切换角色——在地狱的乏火中/按任意键仍使用当前角色）");
	while (1) {
		key = getch();
		if (key == 'Z' || key == 'z') {
			text("附着在尘埃里，喀戎", 1);
			text("藏隐在尘埃里，喀戎");
			text("摘下尘埃的面具，极乐");
			text("口琴内含着万里尘埃，犬吠");
			text("加速！加速——");
			text("-阴凉的尘埃-", 1);
			text("一无所有，");
			text("一无所有！", 1);
			a3(); break;
		}
		else {
			a2_2(); break;
		}
	}
}

void a2() {
	text("开始工作，你搜索了一家国有公司的生产报告……", 1);
	puts("（按【Z键】切换角色——在地狱的乏火中/按任意键仍使用当前角色）");
	while (1) {
		key = getch();
		if (key == 'Z' || key == 'z') {
			text("附着在尘埃里，喀戎", 1);
			text("藏隐在尘埃里，喀戎");
			text("摘下尘埃的面具，极乐");
			text("口琴内含着万里尘埃，犬吠");
			text("加速！加速——");
			text("-阴凉的尘埃-", 1);
			text("一无所有，");
			text("一无所有！", 1);
			a3(); break;
		}
		else {
			a2_1(); break;
		}
	}
}
