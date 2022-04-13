/*题目描述
小明最近学到了汉诺塔。
但是普通的汉诺塔对小明来说太简单了，于是他想到了一种新玩法。
起初有个柱子，个柱子上有一个编号为的圆盘，小明可以合并两个柱子，合并方式如下：
1.选择两个整数，且号柱子上都有圆盘。
2.设柱上共有个圆盘，圆盘编号序列从下至上以此为，柱上共有个圆盘，圆盘编号序列从下至上以此为，现在将它们取下，并按照的顺序放置到柱上，多余的则按原顺序放到最上面。如：,则最终序列为。
小明将合并次，最终所有圆盘都会到一个柱子上，现在给定每次操作的和，你能告诉小明最终圆盘的顺序吗？

输入格式
第一行输入一个正整数
接下来行每行两个正整数，满足上述条件。

输出格式
输出一行个正整数，表示最终的柱子上的圆盘编号从下向上的序列。

输入：
5
1 3
4 2
4 5
1 4

输出：
1 4 3 5 2
*/