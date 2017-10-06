## Tree

### Binary Search Tree
二叉搜索树是一种常用的用来存储和查找数据的树形结构， __它在二维的结构中巧妙地将元素的大小关系也保留下来__ 。符合如下特征：
1. 若任意节点的 __左子树__ 不空， 则 __左子树__ 上所有结点的值均小于它的根结点的值；
2. 若任意节点的 __右子树__ 不空， 则 __右子树__ 上所有结点的值均大于它的根结点的值；
3. 任意节点的左、 右子树也分别为二叉查找树；
4. 没有键值相等的结点。

特别要注意的是这里判别标准是 __左右子树__ 而不是左右结点，并且空树也可以看作是二叉搜索树。二叉查找树相比于其他数据结构的优势在于查找、插入的时间复杂度较低，为O(log n) __这里n为树的高度__ 。一些常用的抽象数据结构，例如set、map等，都是基于二叉搜索树实现，并且一些高级的搜索树，例如红黑树，AVL树，其本质都是二叉搜索树。

二叉搜索树的操作主要有以下几种：

* 元素的查找、插入与删除（包括插入与删除后的平衡） 
* 前序、中序与后序遍历
* 广度优先遍历与深度优先遍历

单独考察树的知识时，基本着重于树的种类的判别（是否是BST、平衡树等），上述的几种操作，及其相应概念与方法的一些变体（计算深度、结点等）。而树作为工具使用时，常用于数据的查询，多用set和map。
```cpp
//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
```

#### Basics
##### 判断是否为BST
这一类方法一般用递归的方法根据定义来判断。而递归的实现可以分为三步：
1. recursion terminator
2. current level processing
3. drill down

按照这个固定的模式可以轻松地写出递归程序，有时其中第二和第三步会混在一起或者交换顺序，待具体情况而定。
* 226.Invert Binary Tree 将二叉树镜像翻转
```cpp
    TreeNode *invertTree(TreeNode *root)
    {
        //recursion terminator
        if (root == NULL)
        {
            return NULL;
        }

        //current level processing
        std::swap(root->left, root->right);

        //drill down
        invertTree(root->left);
        invertTree(root->right);

        return root;
    }
```

递归在BST中的其他应用
* 98 Validate Binary Search Tree
* 101 Symmetric Tree
* 104 Maximum Depth of Binary Tree
* 111 Minimum Depth of Binary Tree
* 235 Lowest Common Ancestor of a Binary Search Tree
* 235 Lowest Common Ancestor of a Binary Tree  


##### BST ←→ Array/Linked list
有序数组、链表转为BST，其一般方法和过程如下图所示，不断的寻找中点，作为当前子树的root结点，然后递归下去。对于链表，可以用快慢指针来寻找中点。
另一种方法是采用中序遍历的方法，因为BST的中序遍历结果就是有序的数组或者链表，而将有序数组、链表转为BST，则是其逆命题。


![array2bst](img/bst/array2bst.gif)
* 109 Convert Sorted List to Binary Search Tree

而将BST转为有序数组，如上所述，采用中序遍历的方法就可以实现目标。

![array2bst](img/bst/bst2array.gif)
* 114 Flatten Binary Tree to Linked List   

#### Query/Insert/Delete/Balance
##### 查找
在二叉搜索树b中查找某个元素x的过程为：
* 若b是空树，则搜索失败，否则：
* 若x等于b的根节点的数据域之值，则查找成功；否则：
* 若x小于b的根节点的数据域之值，则搜索左子树；否则：
* 查找右子树。

![bst_query](img/bst/bst_query.gif)


二叉搜索树的查找过程十分类似于二分查找法，但其优势是二叉搜索树按照中序遍历可以直接输出有序的元素。
##### 插入与删除
二叉搜索树的插入与删除都是基于查找来实现的，超找到对应的位置，再进行操作。以向二叉搜索树b中插入结点s为例，其过程为

* 若b是空树，则将s所指结点作为根节点插入，否则：
* 若s->data等于b的根节点的数据域之值，则返回，否则：
* 若s->data小于b的根节点的数据域之值，则把s所指节点插入到左子树中，否则：
* 把s所指节点插入到右子树中。（新插入节点总是叶子节点）

![bst_insert](img/bst/bst_insert.gif)

二叉搜索树的查找复杂度是与树的高度成比例，但是其在插入或者删除的过程中，可能退化为一个单链表，这时候的查找效率就会大打折扣。所以平衡的作用就是通过变换树的结点的位置，来让所有结点在根节点的两边平均分布，以降低树的高度，达到提高查找效率的目的。

##### 平衡
todo

#### PreOrder/InOrder/PostOrder Traversal
二叉搜索树的三种[遍历方法](https://www.tutorialspoint.com/data_structures_algorithms/tree_traversal.htm)实现形式非常类似，只是处理当前阶段的顺序在前、中、后的差别。具体形式如下：
```cpp
PreOrder(TreeNode *root){
    if(root){
        traverse_path(root);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

InOrder(TreeNode *root){
    if(root){
        InOrder(root->left);
        traverse_path(root);
        InOrder(root->right);
    }
}

PostOrder(TreeNode *root){
    if(root){
        PostOrder(root->left);
        PostOrder(root->right);
        traverse_path(root);
    }
}

```
对于三种遍历方法的实现，这里都可以用递归的方法来实现，而且推荐使用递归的形式来实现。为什么呢？很多人和教材以及网上的资料会告诉你递归要不断进行上下文切换与堆栈的调用，效率低下。但是实际情况中，未必是这样。用STL的栈和队列结构来手动实现递归同样也有会引入很多其他的开销，例如额外变量的创建、拷贝等。而且很多时候STL的操作代码看似很简洁，但是内部却做了很多的事，并且很多人对这些内部处理的开销知之甚少。同时不同应用场景下，影响一个程序效率的因素太多，太多是我们无法掌控的，既然无法掌控，就不能妄加评论说是效率低。

但是我可以肯定的是，大部分情况下，手动实现递归的代码可读性会比递归实现的代码差，这就给维护人员造成很大麻烦，甚至几个月后自己看都看不懂。要记住代码是写给人看的，给计算机运行只是一个额外的功能。你的代码只要能跑起来或者编译通过，那就说明计算机能够理解，这并不难，但要让别人也能一下看懂你的代码，这就很难了。在现在互联网应用的快读开发中，你的代码不可能写完后就永远不改了，实际情况是要经常改动，甚至要由别人来维护。如果你的代码写的简单、清晰明了，让人能很快理解，这让才便于维护，也能更好地重构。从产品角度来讲，这是降低了人月成本，也是提高了效率。

那么BST的递归操作时间复杂度是多少呢？这里的一个方法就是看每个结点访问了几次，这三种遍历方法对每个结点来说都只访问一次，所以时间复杂度都是O(N)，这里N是BST结点的数目。很多递归算法在每一层展开计算时，会有很多重复计算的结点，所以造成时间复杂度呈现指数。最典型的就是裴波那契问题，但是BST的递归每一层其实都是按照树的结构展开的，而BST中的结点又是不交叉重复的，所以不用担心时间复杂度指数增长。

从以上几点来讲，实际开发中，涉及到BST的一些操作，用递归来实现完全就可以。一般来说性能的瓶颈并不在这（这里特指BST的递归）。这里的应用场景是指需要通过裸操作来实现对数据的处理，所以数据量不会很大。对于复杂的或是海量数据，那就建议用专门的框架、库来操作，而且这些库一般都会提供封装好的接口来操作。

__应用__
preorder
* 114 Flatten Binary Tree to Linked List

inorder
* 99 Recover Binary Search Tree


#### BFS/DFS

