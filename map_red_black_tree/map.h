

/**

* implement a container like std::map

*/

#ifndef SJTU_MAP_HPP

#define SJTU_MAP_HPP



// only for std::less<T>

#include <functional>

#include <cstddef>

#include "utility.h"

#include "exceptions.h"



namespace sjtu {   //map，红黑树实现



	template<class Key,class T,class Compare = std::less<Key>>
    class map
	{

	public:

		/**

		* the internal type of data.

		* it should have a default constructor, a copy constructor.

		* You can use sjtu::map as value_type by typedef.

		*/

		typedef pair<const Key, T> value_type;

		/**

		* see BidirectionalIterator at CppReference for help.

		*

		* if there is anything wrong throw invalid_iterator.

		*     like it = map.begin(); --it;

		*       or it = map.end(); ++end();

		*/
		enum RB_Color { red, black };  //节点颜色


		struct Node   //结点
		{
			value_type* value;  //因为key还是有可能没有构造函数，所以value还是要用指针
			Node *parent, *left, *right;
			RB_Color color;
			Node *pre, *next;//前驱与后继
			Node(value_type* val=NULL, RB_Color c = red, Node* p = NULL, Node* l = NULL, Node* r = NULL, Node* pr = NULL, Node* n = NULL)
				:value(val), parent(p), left(l), right(r), color(c), pre(pr), next(n) {}
			~Node(){delete value;}
		};


		class const_iterator;

		class iterator {//迭代器

		private:

			/**

			* TODO add data members

			*   just add whatever you want.

			*/

		public:
			Node* cur;//当前指向
			map* container;  //容器

			iterator() :cur(NULL), container(NULL) {

				// TODO

			}

			iterator(Node* x, map* m) :cur(x), container(m) {}

			iterator(const iterator &other) :cur(other.cur), container(other.container)
			{

				// TODO

			}

			/**

			* return a new iterator which pointer n-next elements

			*   even if there are not enough elements, just return the answer.

			* as well as operator-

			*/

			/**

			* TODO iter++

			*/

			iterator operator++(int)
			{
				iterator temp = *this;
				++*this;
				return temp;
			}

			/**

			* TODO ++iter

			*/

			iterator & operator++()
			{
				if (*this == container->finish)
					throw invalid_iterator();
				cur = cur->next;  //直接找后继
				return *this;
			}

			/**

			* TODO iter--

			*/

			iterator operator--(int)
			{
				iterator temp = *this;
				--*this;
				return temp;
			}

			/**

			* TODO --iter

			*/

			iterator & operator--()
			{
				if (*this == container->start)
					throw invalid_iterator();
				cur = cur->pre;
				return *this;
			}

			/**

			* a operator to check whether two iterators are same (pointing to the same memory).

			*/

			value_type & operator*() const { if (cur and cur->value) return *(cur->value); else throw invalid_iterator(); }

			bool operator==(const iterator &rhs) const { return cur == rhs.cur; }

			bool operator==(const const_iterator &rhs) const { return cur == rhs.cur; }

			/**

			* some other operator for iterator.

			*/

			bool operator!=(const iterator &rhs) const { return cur != rhs.cur; }

			bool operator!=(const const_iterator &rhs) const { return cur != rhs.cur; }



			/**

			* for the support of it->first.

			* See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.  //这个是干嘛的？感觉完全没用到

			*/

			value_type* operator->() const noexcept {return cur->value; }

		};

		class const_iterator {    //常量迭代器

			// it should has similar member method as iterator.

			//  and it should be able to construct from an iterator.

		private:

			// data members.

		public:
			Node *cur;
			const map *container;

			const_iterator() :cur(NULL),container(NULL){

				// TODO

			}

			const_iterator(const const_iterator &other)
				:cur(other.cur),container(other.container)
			{

				// TODO

			}

			const_iterator(const iterator &other)
				:cur(other.cur), container(other.container)
			{

				// TODO

			}

			const_iterator(Node* c,const map* m) :cur(c), container(m)
			{
				// TODO

			}

			// And other methods in iterator.

			// And other methods in iterator.

			// And other methods in iterator.

			/**

			* TODO iter++

			*/

			const_iterator & operator=(iterator &other)
			{
				cur = other.cur;
				container = other.container;
				return *this;
			}

			const_iterator operator++(int)
			{
				const_iterator temp = *this;
				++*this;
				return temp;
			}

			/**

			* TODO ++iter

			*/

			const_iterator & operator++()
			{
				if (*this == container->finish)
					throw invalid_iterator();
				cur = cur->next;
				return *this;
			}

			/**

			* TODO iter--

			*/

			const_iterator operator--(int)
			{
				const_iterator temp = *this;
				--*this;
				return temp;
			}

			/**

			* TODO --iter

			*/



			const_iterator & operator--()
			{
				if (*this == container->start)
					throw invalid_iterator();
				cur = cur->pre;
				return *this;
			}

			/**

			* a operator to check whether two iterators are same (pointing to the same memory).

			*/

			value_type & operator*() const { if (cur and cur->value) return *(cur->value); else throw invalid_iterator(); }

			bool operator==(const iterator &rhs) const { return cur == rhs.cur; }

			bool operator==(const const_iterator &rhs) const { return cur == rhs.cur; }

			/**

			* some other operator for iterator.

			*/

			bool operator!=(const iterator &rhs) const { return cur != rhs.cur; }

			bool operator!=(const const_iterator &rhs) const { return cur != rhs.cur; }



			/**

			* for the support of it->first.

			* See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.

			*/

			value_type* operator->() const noexcept {  return cur->value; }

		};

		/**

		* TODO two constructors

		*/

		//Node* root;
		Node* header;  //header是根节点的父亲，儿子是根节点，左右孩子是最大最小结点，前驱为最大值，没有后继，叶节点儿子是NULL
		int len;
		Compare key_cmp; //key_cmp(a,b)为true表示a<b
		iterator start; //树最小值
		iterator finish; //最大值的后一个结点（实际上就是header，最大值后继节点是header）

		Node* findMin(Node* x) //找最小
		{
			while (x->left != NULL)
				x = x->left;
			return x;
		}
		Node* findMax(Node* x) //找最大
		{
			while (x->right != NULL)
				x = x->right;
			return x;
		}



		map() :len(0)
		{
			header = new Node;    //头节点
			finish = iterator(header, this);
			start = finish;
			key_cmp = Compare();
		}

		Node* findNext(Node* x)  //找到x的后继节点
		{
			if (x == header)  //头节点没有后记
				return NULL;
			if (x->right != 0)
			{
				x = x->right;
				while (x->left != 0)
					x = x->left;
			}
			else
			{
				Node* temp = x->parent;
				while (x == temp->right)
				{
					x = temp;
					temp = temp->parent;
				}
				if (x!=header) //最多找到根，而不是header
					x = temp;
			}
            return x;
		}

		Node* findPre(Node* x)  //找前驱结点，实际上这个函数没用过，还有可能写错了
		{
			if (x == header)
				return NULL;
			if (x->left != 0)
			{
				x = x->left;
				while (x->right != 0)
					x = x->right;
			}
			else
			{
				Node* temp = x->parent;
				while (x == temp->left)
				{
					x = temp;
					temp = temp->parent;
				}
				if (temp->parent != x)
					x = temp;
			}
            return x;
		}

		void cloneNode(Node* &newNode, Node* &oldNode) //递归复制节点和红黑树的关系（不包括前驱后继关系）
		{
			if (oldNode == NULL)
			{
				newNode = NULL;
				return;
			}

			value_type *newValue = new value_type(*(oldNode->value));
			newNode = new Node(newValue, oldNode->color);
			Node *leftNode, *rightNode;

			//std::cout << "clone done\n";

			cloneNode(leftNode, oldNode->left);
			newNode->left = leftNode;
			if(leftNode)
				leftNode->parent = newNode;

			//std::cout << "left done\n";

			cloneNode(rightNode, oldNode->right);
			newNode->right = rightNode;
			if (rightNode)
				rightNode->parent = newNode;
			//std::cout << "right done\n";
		}

		map(const map &other) :len(other.len), key_cmp(other.key_cmp) //复制构造函数
		{
			if (other.size() == 0)  //为空
			{
				header = new Node;
				finish = iterator(header, this);
				start = finish;
				key_cmp = Compare();
			}
			else
			{
				header = new Node;
				Node *temp, *preNode, *nextNode;
				cloneNode(temp, other.header->parent); //复制整棵树
				header->parent = temp;  
				temp->parent = header;  //头节点和根结点关系
				header->left = findMin(temp); //找到最小值
				header->right = findMax(temp); //找到最大值
				preNode = header->left;       //构建从最小值开始前驱后继关系
				while (preNode != header->right)
				{
					nextNode = findNext(preNode);
					preNode->next = nextNode;
					nextNode->pre = preNode;
					preNode = nextNode;
				}
				//std::cout<<"link done\n";
				header->pre = preNode; //header前驱为最大值，没有后继
				preNode->next = header;


				finish = iterator(header, this);
				start = iterator(header->left, this);
			}

		}

		/**

		* TODO assignment operator

		*/

		map & operator=(const map &other)  //赋值
		{
			if (&other == this) //避免自我复制
				return *this;

			clear();  //清除原来，复制同复制构造函数
			len = other.len;
			//std::cout <<"len "<<len<< "\n";
			key_cmp = other.key_cmp;
			if (other.size() == 0)
			{
				//header = new Node;
				finish = iterator(header, this);
				start = finish;
				key_cmp = Compare();
				return *this;
			}
			else
			{
				Node *temp, *preNode, *nextNode;
				//std::cout << "before clone\n";
				cloneNode(temp, other.header->parent);
				//std::cout << "After clone\n";
				header->parent = temp;
				temp->parent = header;
				header->left = findMin(temp);
				header->right = findMax(temp);
				preNode = header->left;
				while (preNode != header->right)
				{
					nextNode = findNext(preNode);
					preNode->next = nextNode;
					nextNode->pre = preNode;
					preNode = nextNode;
				}
				header->pre = preNode;
				preNode->next = header;


				finish = iterator(header, this);
				start = iterator(header->left, this);
				//std::cout << "size inside " << len << "\n";
				return *this;
			}
		}
		/**

		* clears the contents

		*/

		void clear()
		{
			if (len == 0) return;
			//std::cout << "not distory" << Integer::counter << std::endl;
			Node* oldNode = start.cur, *temp;      //从最小值开始，利用前驱后继关系顺序删除，
			//std::cout << "start.cur==header??? " << (oldNode == header) << "\n";
			while (oldNode != header)
			{
				//std::cout << "not distory" << Integer::counter << std::endl;
				temp = oldNode->next;
				delete oldNode;
				oldNode = temp;
			}
			header->parent = NULL;  //维护header，start，finish
			header->left = NULL;
			header->right = NULL;
			header->pre = NULL;
			header->next = NULL;
			finish = iterator(header, this);
			start = finish;
			len = 0;
		}

		/**

		* TODO Destructors

		*/

		~map()
		{
			//std::cout << "not distory before clear  " << Integer::counter << std::endl;
			clear();
			//std::cout << "not distory after clear " << Integer::counter << std::endl;
			delete header;
		}

		/**

		* TODO

		* access specified element with bounds checking

		* Returns a reference to the mapped value of the element with key equivalent to key.

		* If no such element exists, an exception of type `index_out_of_bound'

		*/

		T & at(const Key &key)    //访问
		{
			Node* temp = header->parent;
			while (temp != NULL)  //从根开始查找
			{
				if (key_cmp(key, temp->value->first))
					temp = temp->left;
				else if (key_cmp(temp->value->first, key))
					temp = temp->right;
				else
					break;
			}
			if (temp == NULL)
				throw index_out_of_bound();
			return temp->value->second;
		}

		const T & at(const Key &key) const  //不允许修改
		{
			Node* temp = header->parent;
			while (temp != NULL)
			{
				if (key_cmp(key, temp->value->first))
					temp = temp->left;
				else if (key_cmp(temp->value->first, key))
					temp = temp->right;
				else
					break;
			}
			if (temp == NULL)
				throw index_out_of_bound();
			return temp->value->second;
		}

		/**

		* TODO

		* access specified element

		* Returns a reference to the value that is mapped to a key equivalent to key,

		*   performing an insertion if such key does not already exist.

		*/

		T & operator[](const Key &key)
		{
			Node* temp = header->parent;
			//if(key_cmp(key, (start.cur)->value->first) or key_cmp(header->right->value->first,key))
				//temp = (insert(value_type(key, T()))).first.cur;
			while (temp != NULL)
			{
				if (key_cmp(key, temp->value->first))
					temp = temp->left;
				else if (key_cmp(temp->value->first, key))
					temp = temp->right;
				else
					break;
			}
			if (temp == NULL)  //没有找到就插入
			{
				//cout << "len before insert " << len << endl;;
				temp = (insert(value_type(key, T()))).first.cur;
			}
			//cout << "len " << len << "\n";
			return temp->value->second;
		}

		/**

		* behave like at() throw index_out_of_bound if such key does not exist.

		*/

		const T & operator[](const Key &key) const  //没有找到抛出异常
		{
			Node* temp = header->parent;
			while (temp != NULL)
			{
				if (key_cmp(key, temp->value->first))
					temp = temp->left;
				else if (key_cmp(temp->value->first, key))
					temp = temp->right;
				else
					break;
			}
			if (temp == NULL)
				throw index_out_of_bound();
			return temp->value->second;
		}

		/**

		* return a iterator to the beginning

		*/

		iterator begin() { return start; }

		const_iterator cbegin() const { return const_iterator(start); }

		/**

		* return a iterator to the end

		* in fact, it returns past-the-end.

		*/

		iterator end() { return finish; }

		const_iterator cend() const { return const_iterator(finish); }

		/**

		* checks whether the container is empty

		* return true if empty, otherwise false.

		*/

		bool empty() const { return len == 0; }

		/**

		* returns the number of elements.

		*/

		int size() const { return len; }



		/**

		* insert an element.

		* return a pair, the first of the pair is

		*   the iterator to the new element (or the element that prevented the insertion),

		*   the second one is true if insert successfully, or false.

		*/

		pair<iterator, bool> insert(const value_type &value)
		{
			Node* y = header, *x = header->parent;
			bool cmp = true;
			while (x != NULL)  //找到插入节点
			{
				y = x;
				cmp = key_cmp(value.first, (x->value)->first);
				x = cmp ? x->left : x->right;
			}  //y是插入节点的父亲
			iterator ins = iterator(y,this);
			if (cmp)  //x现在是NULL，如果之前还是x小于前一个
				if (ins == start)  //x的父节点是start，在start插入
					return pair<iterator, bool>(_insert(x, y, value), true);
				else
					--ins;  //找到x的前一个，就是要x插入的位置
			if (key_cmp(((ins.cur)->value)->first, value.first)) //如果ins比value要小，就确认y是要插入的父节点
				return pair<iterator, bool>(_insert(x, y, value), true);
			return  pair<iterator, bool>(ins, false);
		}

		iterator _insert(Node* pos, Node* par, value_type value)  //真正的插入
		{
			value_type *val = new value_type(value);  
			Node* temp = new Node(val), *tempNext;  //新节点
			temp->parent = par;
			if (par == header or pos != NULL or key_cmp(value.first, (par->value)->first))  //新插入节点是左儿子
			{
				par->left = temp;
				if (par == header)  //调整最小值和start
				{
					header->parent = temp;
					header->right = temp;
					//temp->next = header;
					//header->pre = temp;
					start.cur = temp;
				}
				if (par == header->left)
				{
					header->left = temp;
					//par->pre = temp;
					//temp->next = par;
					start.cur = temp;
				}
			}
			else   //右儿子
			{
				par->right = temp;
				if (par == header->right)
					header->right = temp;
			}
			len++;
			tempNext = findNext(temp);  //前驱和后继
			temp->next = tempNext;
			if (tempNext)
			{
				temp->pre = tempNext->pre;
				if (tempNext->pre)
					tempNext->pre->next = temp;
				tempNext->pre = temp;
			}
			rebalance(temp, header->parent);  //平衡
			return iterator(temp,this);
		}

		/**

		* erase the element at pos.

		*
 		* throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)

		*/

		void erase(iterator pos)  //删除
		{
			if (pos == finish or pos.container != this or len == 0)  //边界判断
				throw invalid_iterator();

			if (pos.cur->pre)
				pos.cur->pre->next = pos.cur->next;
			if (pos.cur->next)
				pos.cur->next->pre = pos.cur->pre;  //更改前驱后继关系
			Node* del = _rebalance_erase(pos.cur, header->parent, header->left, header->right);  //重新平衡
			delete del;  //删除
			start.cur = header->left;  //维护finish，start，len等信息
			finish.cur = header;
			len--;
			if (len == 0)
			{
				//std::cout << "\ndone\n";
				header->parent = NULL;
				header->left = NULL;
				header->right = NULL;
				header->pre = NULL;
				header->next = NULL;
				finish = iterator(header, this);
				start = finish;
			}
		}

		/**

		* Returns the number of elements with key

		*   that compares equivalent to the specified argument,

		*   which is either 1 or 0

		*     since this container does not allow duplicates.

		* The default method of check the equivalence is !(a < b || b > a)

		*/

		int count(const Key &key) const //必须要加const，否则const map会出问题
		{
			if (find(key)==finish) 
				return 0;
			else
				return 1;
		}

		/**

		* Finds an element with key equivalent to key.

		* key value of the element to search for.

		* Iterator to an element with key equivalent to key.

		*   If no such element is found, past-the-end (see end()) iterator is returned.

		*/

		iterator find(const Key &key)
		{
			Node* temp = header->parent;
			while (temp != NULL)
			{
				if (key_cmp(key, temp->value->first))
					temp = temp->left;
				else if (key_cmp(temp->value->first, key))
					temp = temp->right;
				else
					break;
			}
			if (temp == NULL)
				return finish;
			return iterator(temp, this);
		}

		const_iterator find(const Key &key) const   //const总是有问题
		{
			Node* temp = header->parent;
			while (temp != NULL)
			{
				if (key_cmp(key, temp->value->first))
					temp = temp->left;
				else if (key_cmp(temp->value->first, key))
					temp = temp->right;
				else
					break;
			}
			if (temp == NULL)
				return const_iterator(finish);
			//tmp.cur=temp;
			//tmp.container = this;
   			return const_iterator(temp, this);
		}

		void rotate_left(Node* x, Node* &root)  //左旋
		{
			Node* y = x->right;
			x->right = y->left;
			if (y->left != NULL)
				y->left->parent = x;
			y->parent = x->parent;
			if (x == root)
				root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}
		void rotate_right(Node* x, Node* &root)  //右旋
		{
			Node* y = x->left;
			x->left = y->right;
			if (y->right != NULL)
				y->right->parent = x;
			y->parent = x->parent;
			if (x == root)
				root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		void rebalance(Node* x, Node* &root)
		{
			x->color = red;
			while (x != root and x->parent->color == red)//x父亲为红色
			{
				if (x->parent == x->parent->parent->left)//X父亲为祖父左儿子
				{
					Node* y = x->parent->parent->right;//y为x的叔节点
					if (y and y->color == red)  //叔节点为红，调整颜色
					{
						x->parent->color = black;//X的父节点着黑色
						y->color = black;//X的叔节点Y着黑色
						x->parent->parent->color = red;//X的祖父节点着红色
						x = x->parent->parent; //x变为祖父节点，向上调整
					}
					else//X的叔节点不存在（视为黑色）或者为黑色
					{
						if (x == x->parent->right)//X为右儿子，即内侧插入（左右）
						{
							x = x->parent;//设置旋转点为X的父节点，不影响后面if外X的值
							rotate_left(x, root);//以X(实际为原X的父节点)为旋转点左旋转
						}//x指向原来父节点，但是父节点和原来插入节点交换了父子关系，所以现在x仍然是孙子节点
						x->parent->color = black;//将X的父节点着黑色
						x->parent->parent->color = red;//X的祖父节点变为红色
						rotate_right(x->parent->parent, root);//以X的祖父节点为旋转点右旋转
					}
				}
				else //X父亲为祖父右儿子
				{
					Node* y = x->parent->parent->left;//Y为X的叔节点
					if (y && y->color == red)//如果X的叔节点存在且为红色
					{				//调整颜色，并向上迭代判断调整
						x->parent->color = black;
						y->color = black;
						x->parent->parent->color = red;
						x = x->parent->parent;
					}
					else
					{
						if (x == x->parent->left)
						{
							x = x->parent;
							rotate_right(x, root);//以X(原X的父节点)为旋转点，右旋转（旋转后指向是原来的p，但是地址没有变，是指向改了）
						}
						x->parent->color = black;
						x->parent->parent->color = red;
						rotate_left(x->parent->parent, root);//以X的祖父节点为旋转点进行左旋转
					}

				}
			}
			root->color = black;
		}

		Node* _rebalance_erase(Node* z, Node* &root, Node* &leftmost, Node* &rightmost) //自底向上
		{
			Node* y = z;
			Node* x = NULL;
			Node* x_parent = NULL;
			if (y->left == 0)             // z没有左儿子
				x = y->right;               // x为右儿子（可能为空）
			else if (y->right == 0)          // z 没有右儿子
				x = y->left;              // x为左儿子（非空）
			else
			{                      // z 有两个儿子
				y = y->right;
				while (y->left != 0)
					y = y->left;
				x = y->right;
			}
			if (y != z)
			{                 // 有两个孩子，找替身
				z->left->parent = y;
				y->left = z->left;
				if (y != z->right)
				{
					x_parent = y->parent;
					if (x)
						x->parent = y->parent;
					y->parent->left = x;      // y 是左孩子
					y->right = z->right;
					z->right->parent = y;
				}
				else
					x_parent = y;
				if (root == z)
					root = y;
				else if (z->parent->left == z)
					z->parent->left = y;
				else
					z->parent->right = y;
				y->parent = z->parent;

				RB_Color temp = y->color;
				y->color = z->color;
				z->color = temp;
				y = z;    //之前y完全替代了z，x是需要被调整平衡的节点，y=z后，y是可以被删除的z节点
			}
			else
			{// y == z   有一个或者没有孩子
				x_parent = y->parent;
				if (x)
					x->parent = y->parent;
				if (root == z)
					root = x;
				else
					if (z->parent->left == z)
						z->parent->left = x;
					else
						z->parent->right = x;
				if (leftmost == z)
					if (z->right == 0)        // z->left 也是NULL
						leftmost = z->parent;    // z是根节点，就让leftmost == header
					else
						leftmost = findMin(x);
				if (rightmost == z)
					if (z->left == 0)         // z->right 也是NULL
						rightmost = z->parent;      // 说明z==root，让 rightmost = header
					else                      // x == z->left
						rightmost = findMax(x);

			}

			//以下是调整平衡
			if (y->color != red)  //红色不用调整
			{
				while (x != root && (x == 0 || x->color == black))  //待调整节点d为黑
					if (x == x_parent->left)   //左儿子
					{
						Node* w = x_parent->right;
						if (w->color == red)    //待调整节点兄弟s为红色
						{
							w->color = black;     //s变黑
							x_parent->color = red;  //父节点p变红
							rotate_left(x_parent, root); //左旋
							w = x_parent->right;  //新的兄弟节点
						}
						if ((w->left == 0 || w->left->color == black) &&
							(w->right == 0 || w->right->color == black)) //兄弟节点S左右儿子均为黑色
						{
							w->color = red;   //兄弟节点改为红色
							x = x_parent;     //调整节点改为父节点p
							x_parent = x_parent->parent;
						}
						else
						{
							if (w->right == 0 || w->right->color == black)  //兄弟节点S的右儿子为黑色
							{
								if (w->left)
									w->left->color = black;  //s左儿子着黑
								w->color = red;              //s着红
								rotate_right(w, root);       //s右旋
								w = x_parent->right;         //s变为原来s儿子
							}
							w->color = x_parent->color;     //s与父节点p交换颜色
							x_parent->color = black;
							if (w->right)
								w->right->color = black;    //s的右儿子变为黑色
							rotate_left(x_parent, root);    //父亲左旋
							break;
						}
					}
					else
					{                  // 调整节点是右儿子，同上
						Node* w = x_parent->left;
						if (w->color == red)
						{
							w->color = black;
							x_parent->color = red;
							rotate_right(x_parent, root);
							w = x_parent->left;
						}
						if ((w->right == 0 || w->right->color == black) &&
							(w->left == 0 || w->left->color == black))
						{
							w->color = red;
							x = x_parent;
							x_parent = x_parent->parent;
						}
						else
						{
							if (w->left == 0 || w->left->color == black)
							{
								if (w->right) w->right->color = black;
								w->color = red;
								rotate_left(w, root);
								w = x_parent->left;
							}
							w->color = x_parent->color;
							x_parent->color = black;
							if (w->left) w->left->color = black;
							rotate_right(x_parent, root);
							break;
						}
					}
				if (x)
					x->color = black;  //调整节点不为空则改为黑色；
			}
			return y;
		}

	};





}



#endif
