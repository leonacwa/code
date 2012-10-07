## Suffix Automaton 后缀自动机  

### 某些要点  [个人理解]
p->f，这里的f相当于失败指针fail，与KMP的next函数和AC自动机的fail指针相似，我感觉是一样的.  
一个难点在复制一个存在的节点q为nq，并将q->f标为nq。
其实这点我也没想明白，似懂非懂的。感觉是为了不让整个后缀自动机接受一些非法状态，我觉得还有一个就是不能让后缀自动机把一些合法状态给去掉了，而这样做就能处理好。
在http://hi.baidu.com/myidea/item/142c5cd45901a51820e25039的博文中，构建"aabbabd"的sam，当构建到aabb时，因为上一次购构建到aab，b是最后的一个节点，b是合法的后缀，加入一个新b后，b仍是合法后缀，bb也是合法后缀，abb也是合法后缀，现在还没有问题，但是在第一个b的f，也就是根S后加b时，已经有一个b了，如果此时停下算法，不在S后加，并且把第2个b的f设为第个b，这样的话，还是能够接受aabb的后缀，但是，在接受b这个后缀时，找不到了！因为没有一个到终止处长度为1的状态，如果把第一个b作为终止状态，长度是3，这个状态对于后缀b是不合法的，把bbb字符串放入sam匹配，会从第1个b匹配到第2个b，长度是3+1，这个状态有问题了。  
既然第1个b设为b2的长度是3，第二个b设为b2，b1到b2不能接受bb，我们可以建立S->b->b的路径，那么我们就复制b1为nb，有S->nb->b2，S指向nb，nb接受S->b->b的合法状态，b1接受S->a->a->b的合法状态，并且b1->f = nb, b2->f = nb
  
<pre>
<code>
void append(char ch) { /* 添加一个字符到末尾，last为一个后缀终止态，沿着last->f走，经过的都是终止态 */
	int c = ch - 'a';
	Node *p = last, *np = pool + cnt++;
	memset(np, 0, sizeof(Node));
	np->len = last->len + 1;
	last = np;
	for (; NULL != p && NULL == p->ch[c]; p = p->f) p->ch[c] = np;
	if (p == NULL) {
		np->f = root;
	} else {
		if (p->ch[c]->len == p->len+1) {
			np->f = p->ch[c];
		} else { /* 新建一个节点，避免接受不存在的后缀 */
			Node *q = p->ch[c], *nq = pool + cnt++;
			*nq = *q;
			nq->len = p->len + 1;
			q->f = np->f = nq;
			for (; NULL != p && p->ch[c] == q; p = p->f) p->ch[c] = nq;
		}
	}
}
<code>
</pre>
  
### 性质  

接受的是后缀的状态，不过也能用来接受子串，只不过不会在后缀终点而已
从最后一个插入的节点last出发，沿着f（或者是pre、par、fail）指向的节点走，走过的节点都是后缀终点，也就是一个后缀。

http://hi.baidu.com/wyl8899/item/fe30282b5f7c4dd50f37f96d
陈立杰ppt：  
一些定义和符号表示上的约定：  
Right(str)是S的连续子串str在S中结束位置的集合，|Right(str)|即str在S中出现的次数。  
对于一个状态s，其所有能接受的子串str的Right集合都是相同的，据此定义Right(s)为状态s所能接受的子串在S中结束位置的集合。  
trans(s,x)是状态s在输入了字符x后转移到的状态。如果为0表示没有这个转移。  
Max(s)和Min(s)是状态s能够接受的最长的和最短子串的长度。  
pre(s)是状态s的父节点。这个父节点的定义比较乱糟...个人比较倾向于CLJ的ppt里的定义：  
pre(s)=使得Right(x)包含Right(s)且|Right(x)|最小的x。  
事实上，对于一个SAM，从最后一个节点(使得Max(s)=|S|的唯一状态s)出发，沿着pre链走，就可以找到所有的接受态的节点。  
记init为自动机的初态。  

一些性质：  
从init出发并终止于接受态的路径，和S的所有后缀一一对应。  
从init出发并终止于任意状态的路径，和S的所有子串一一对应。  
一个状态s能接受的子串的长度是连续的区间，即[Min(s),Max(s)]。  
对于一个状态s，其所有能接受的子串str的Right集合都是相同的。(这在定义的时候已经用到了)  
对于任意的状态s，pre(s)是使得Right(x)包含Right(s)且|Right(x)|最小的x。(定义)  
对于任意两个不同的状态s1,s2，Right(s1)和Right(s2)要么没有交集，要么互相包含。(证明见CLJ的ppt)  
对于任意的非init的状态s，有Min(s)-1=Max(pre(s))。(同上)  
pre关系构成一颗树，称为pre树。对于任意的状态s，Right(s)是pre树中以s为根的子树的所有节点的Right集合的并集。  
进一步地，根据Right集合不包含即相交的性质，Right(s)是pre树中以s为根的子树中所有叶子节点的Right集合的并集。  


http://hi.baidu.com/wyl8899/item/fe30282b5f7c4dd50f37f96d
每个节点s所能接受的子串们在母串S中出现的次数，即|Right(s)|，等于从这个节点出发能走到接受态节点的路径数。  

http://www.acforfun.com/?p=81
1.每个子串对应于一条从s点出发的路径，每一条路径也对应于一个子串。  
2.每个结点对应于一系列路径，即一系列子串，且这些子串的长度连续，短串必然是长串的后缀。即若某结点对应的最长子串为s1，最短为s2，则s2是s1的后缀，并且该结点也对应了长度大于len[s2]的其他s1的后缀。  
3.设结点n对应的最短子串长度为L，则fail[n]对应的最长子串长度为L-1。  
4.所有走到终止状态的路径都是后缀。  

http://blog.sina.com.cn/s/blog_7812e98601012dfv.html
a. 所有的子串都能够由s走到
b. 所有的后缀都能够被s走到
c. 所有走到终止状态的路径都是后缀
d. 走到一个点的路径都是不同的，且为连续的一段长度。
e. 设a的f是b，那么b的集合是s到a的路径的最大子集。

