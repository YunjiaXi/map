

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



namespace sjtu {   //map�������ʵ��



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
		enum RB_Color { red, black };  //�ڵ���ɫ


		struct Node   //���
		{
			value_type* value;  //��Ϊkey�����п���û�й��캯��������value����Ҫ��ָ��
			Node *parent, *left, *right;
			RB_Color color;
			Node *pre, *next;//ǰ������
			Node(value_type* val=NULL, RB_Color c = red, Node* p = NULL, Node* l = NULL, Node* r = NULL, Node* pr = NULL, Node* n = NULL)
				:value(val), parent(p), left(l), right(r), color(c), pre(pr), next(n) {}
			~Node(){delete value;}
		};


		class const_iterator;

		class iterator {//������

		private:

			/**

			* TODO add data members

			*   just add whatever you want.

			*/

		public:
			Node* cur;//��ǰָ��
			map* container;  //����

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
				cur = cur->next;  //ֱ���Һ��
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

			* See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.  //����Ǹ���ģ��о���ȫû�õ�

			*/

			value_type* operator->() const noexcept {return cur->value; }

		};

		class const_iterator {    //����������

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
		Node* header;  //header�Ǹ��ڵ�ĸ��ף������Ǹ��ڵ㣬���Һ����������С��㣬ǰ��Ϊ���ֵ��û�к�̣�Ҷ�ڵ������NULL
		int len;
		Compare key_cmp; //key_cmp(a,b)Ϊtrue��ʾa<b
		iterator start; //����Сֵ
		iterator finish; //���ֵ�ĺ�һ����㣨ʵ���Ͼ���header�����ֵ��̽ڵ���header��

		Node* findMin(Node* x) //����С
		{
			while (x->left != NULL)
				x = x->left;
			return x;
		}
		Node* findMax(Node* x) //�����
		{
			while (x->right != NULL)
				x = x->right;
			return x;
		}



		map() :len(0)
		{
			header = new Node;    //ͷ�ڵ�
			finish = iterator(header, this);
			start = finish;
			key_cmp = Compare();
		}

		Node* findNext(Node* x)  //�ҵ�x�ĺ�̽ڵ�
		{
			if (x == header)  //ͷ�ڵ�û�к��
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
				if (x!=header) //����ҵ�����������header
					x = temp;
			}
            return x;
		}

		Node* findPre(Node* x)  //��ǰ����㣬ʵ�����������û�ù������п���д����
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

		void cloneNode(Node* &newNode, Node* &oldNode) //�ݹ鸴�ƽڵ�ͺ�����Ĺ�ϵ��������ǰ����̹�ϵ��
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

		map(const map &other) :len(other.len), key_cmp(other.key_cmp) //���ƹ��캯��
		{
			if (other.size() == 0)  //Ϊ��
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
				cloneNode(temp, other.header->parent); //����������
				header->parent = temp;  
				temp->parent = header;  //ͷ�ڵ�͸�����ϵ
				header->left = findMin(temp); //�ҵ���Сֵ
				header->right = findMax(temp); //�ҵ����ֵ
				preNode = header->left;       //��������Сֵ��ʼǰ����̹�ϵ
				while (preNode != header->right)
				{
					nextNode = findNext(preNode);
					preNode->next = nextNode;
					nextNode->pre = preNode;
					preNode = nextNode;
				}
				//std::cout<<"link done\n";
				header->pre = preNode; //headerǰ��Ϊ���ֵ��û�к��
				preNode->next = header;


				finish = iterator(header, this);
				start = iterator(header->left, this);
			}

		}

		/**

		* TODO assignment operator

		*/

		map & operator=(const map &other)  //��ֵ
		{
			if (&other == this) //�������Ҹ���
				return *this;

			clear();  //���ԭ��������ͬ���ƹ��캯��
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
			Node* oldNode = start.cur, *temp;      //����Сֵ��ʼ������ǰ����̹�ϵ˳��ɾ����
			//std::cout << "start.cur==header??? " << (oldNode == header) << "\n";
			while (oldNode != header)
			{
				//std::cout << "not distory" << Integer::counter << std::endl;
				temp = oldNode->next;
				delete oldNode;
				oldNode = temp;
			}
			header->parent = NULL;  //ά��header��start��finish
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

		T & at(const Key &key)    //����
		{
			Node* temp = header->parent;
			while (temp != NULL)  //�Ӹ���ʼ����
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

		const T & at(const Key &key) const  //�������޸�
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
			if (temp == NULL)  //û���ҵ��Ͳ���
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

		const T & operator[](const Key &key) const  //û���ҵ��׳��쳣
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
			while (x != NULL)  //�ҵ�����ڵ�
			{
				y = x;
				cmp = key_cmp(value.first, (x->value)->first);
				x = cmp ? x->left : x->right;
			}  //y�ǲ���ڵ�ĸ���
			iterator ins = iterator(y,this);
			if (cmp)  //x������NULL�����֮ǰ����xС��ǰһ��
				if (ins == start)  //x�ĸ��ڵ���start����start����
					return pair<iterator, bool>(_insert(x, y, value), true);
				else
					--ins;  //�ҵ�x��ǰһ��������Ҫx�����λ��
			if (key_cmp(((ins.cur)->value)->first, value.first)) //���ins��valueҪС����ȷ��y��Ҫ����ĸ��ڵ�
				return pair<iterator, bool>(_insert(x, y, value), true);
			return  pair<iterator, bool>(ins, false);
		}

		iterator _insert(Node* pos, Node* par, value_type value)  //�����Ĳ���
		{
			value_type *val = new value_type(value);  
			Node* temp = new Node(val), *tempNext;  //�½ڵ�
			temp->parent = par;
			if (par == header or pos != NULL or key_cmp(value.first, (par->value)->first))  //�²���ڵ��������
			{
				par->left = temp;
				if (par == header)  //������Сֵ��start
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
			else   //�Ҷ���
			{
				par->right = temp;
				if (par == header->right)
					header->right = temp;
			}
			len++;
			tempNext = findNext(temp);  //ǰ���ͺ��
			temp->next = tempNext;
			if (tempNext)
			{
				temp->pre = tempNext->pre;
				if (tempNext->pre)
					tempNext->pre->next = temp;
				tempNext->pre = temp;
			}
			rebalance(temp, header->parent);  //ƽ��
			return iterator(temp,this);
		}

		/**

		* erase the element at pos.

		*
 		* throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)

		*/

		void erase(iterator pos)  //ɾ��
		{
			if (pos == finish or pos.container != this or len == 0)  //�߽��ж�
				throw invalid_iterator();

			if (pos.cur->pre)
				pos.cur->pre->next = pos.cur->next;
			if (pos.cur->next)
				pos.cur->next->pre = pos.cur->pre;  //����ǰ����̹�ϵ
			Node* del = _rebalance_erase(pos.cur, header->parent, header->left, header->right);  //����ƽ��
			delete del;  //ɾ��
			start.cur = header->left;  //ά��finish��start��len����Ϣ
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

		int count(const Key &key) const //����Ҫ��const������const map�������
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

		const_iterator find(const Key &key) const   //const����������
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

		void rotate_left(Node* x, Node* &root)  //����
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
		void rotate_right(Node* x, Node* &root)  //����
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
			while (x != root and x->parent->color == red)//x����Ϊ��ɫ
			{
				if (x->parent == x->parent->parent->left)//X����Ϊ�游�����
				{
					Node* y = x->parent->parent->right;//yΪx����ڵ�
					if (y and y->color == red)  //��ڵ�Ϊ�죬������ɫ
					{
						x->parent->color = black;//X�ĸ��ڵ��ź�ɫ
						y->color = black;//X����ڵ�Y�ź�ɫ
						x->parent->parent->color = red;//X���游�ڵ��ź�ɫ
						x = x->parent->parent; //x��Ϊ�游�ڵ㣬���ϵ���
					}
					else//X����ڵ㲻���ڣ���Ϊ��ɫ������Ϊ��ɫ
					{
						if (x == x->parent->right)//XΪ�Ҷ��ӣ����ڲ���루���ң�
						{
							x = x->parent;//������ת��ΪX�ĸ��ڵ㣬��Ӱ�����if��X��ֵ
							rotate_left(x, root);//��X(ʵ��ΪԭX�ĸ��ڵ�)Ϊ��ת������ת
						}//xָ��ԭ�����ڵ㣬���Ǹ��ڵ��ԭ������ڵ㽻���˸��ӹ�ϵ����������x��Ȼ�����ӽڵ�
						x->parent->color = black;//��X�ĸ��ڵ��ź�ɫ
						x->parent->parent->color = red;//X���游�ڵ��Ϊ��ɫ
						rotate_right(x->parent->parent, root);//��X���游�ڵ�Ϊ��ת������ת
					}
				}
				else //X����Ϊ�游�Ҷ���
				{
					Node* y = x->parent->parent->left;//YΪX����ڵ�
					if (y && y->color == red)//���X����ڵ������Ϊ��ɫ
					{				//������ɫ�������ϵ����жϵ���
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
							rotate_right(x, root);//��X(ԭX�ĸ��ڵ�)Ϊ��ת�㣬����ת����ת��ָ����ԭ����p�����ǵ�ַû�б䣬��ָ����ˣ�
						}
						x->parent->color = black;
						x->parent->parent->color = red;
						rotate_left(x->parent->parent, root);//��X���游�ڵ�Ϊ��ת���������ת
					}

				}
			}
			root->color = black;
		}

		Node* _rebalance_erase(Node* z, Node* &root, Node* &leftmost, Node* &rightmost) //�Ե�����
		{
			Node* y = z;
			Node* x = NULL;
			Node* x_parent = NULL;
			if (y->left == 0)             // zû�������
				x = y->right;               // xΪ�Ҷ��ӣ�����Ϊ�գ�
			else if (y->right == 0)          // z û���Ҷ���
				x = y->left;              // xΪ����ӣ��ǿգ�
			else
			{                      // z ����������
				y = y->right;
				while (y->left != 0)
					y = y->left;
				x = y->right;
			}
			if (y != z)
			{                 // ���������ӣ�������
				z->left->parent = y;
				y->left = z->left;
				if (y != z->right)
				{
					x_parent = y->parent;
					if (x)
						x->parent = y->parent;
					y->parent->left = x;      // y ������
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
				y = z;    //֮ǰy��ȫ�����z��x����Ҫ������ƽ��Ľڵ㣬y=z��y�ǿ��Ա�ɾ����z�ڵ�
			}
			else
			{// y == z   ��һ������û�к���
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
					if (z->right == 0)        // z->left Ҳ��NULL
						leftmost = z->parent;    // z�Ǹ��ڵ㣬����leftmost == header
					else
						leftmost = findMin(x);
				if (rightmost == z)
					if (z->left == 0)         // z->right Ҳ��NULL
						rightmost = z->parent;      // ˵��z==root���� rightmost = header
					else                      // x == z->left
						rightmost = findMax(x);

			}

			//�����ǵ���ƽ��
			if (y->color != red)  //��ɫ���õ���
			{
				while (x != root && (x == 0 || x->color == black))  //�������ڵ�dΪ��
					if (x == x_parent->left)   //�����
					{
						Node* w = x_parent->right;
						if (w->color == red)    //�������ڵ��ֵ�sΪ��ɫ
						{
							w->color = black;     //s���
							x_parent->color = red;  //���ڵ�p���
							rotate_left(x_parent, root); //����
							w = x_parent->right;  //�µ��ֵܽڵ�
						}
						if ((w->left == 0 || w->left->color == black) &&
							(w->right == 0 || w->right->color == black)) //�ֵܽڵ�S���Ҷ��Ӿ�Ϊ��ɫ
						{
							w->color = red;   //�ֵܽڵ��Ϊ��ɫ
							x = x_parent;     //�����ڵ��Ϊ���ڵ�p
							x_parent = x_parent->parent;
						}
						else
						{
							if (w->right == 0 || w->right->color == black)  //�ֵܽڵ�S���Ҷ���Ϊ��ɫ
							{
								if (w->left)
									w->left->color = black;  //s������ź�
								w->color = red;              //s�ź�
								rotate_right(w, root);       //s����
								w = x_parent->right;         //s��Ϊԭ��s����
							}
							w->color = x_parent->color;     //s�븸�ڵ�p������ɫ
							x_parent->color = black;
							if (w->right)
								w->right->color = black;    //s���Ҷ��ӱ�Ϊ��ɫ
							rotate_left(x_parent, root);    //��������
							break;
						}
					}
					else
					{                  // �����ڵ����Ҷ��ӣ�ͬ��
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
					x->color = black;  //�����ڵ㲻Ϊ�����Ϊ��ɫ��
			}
			return y;
		}

	};





}



#endif
