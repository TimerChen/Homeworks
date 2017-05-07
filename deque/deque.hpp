#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"
#include "utility.hpp"

#include <cstddef>
//Can I use cmath ?
#include <cmath>

namespace sjtu {

template<class T>
class list
{
	template<class D_T>
	friend class deque;

	struct Node
	{
		Node();
		~Node(){if(data)delete data;}
		T *data;int extra;
		Node *pre,*next;
	},*&BEGIN,END[1];
	int SIZE;
	void clear(Node *l = BEGIN)
	{
		SIZE=0;
		for(;l!=data.END;l=l->next)
			delete l;
	}
	Node *insert(Node *l, const T &val)
	{
		SIZE++;
		Node *r = new Node();
		r->data = new T(val);
		r->pre = l;r->next=l->next;
		l->next=r;
		return r;
	}
	void remove(Node *l)
	{
		if(l == end) throw(invalid_iterator());
		SIZE--;
		l->next->pre = l->pre;
		l->pre->next = l->next;
		delete l;
	}
public:
	list():BEGIN(END->next)
	{END[0]->extra = -1;SIZE=0;}
	~list(){data.clear();blocks.clear();}
};
template<class T>
list<T>::Node()
{
	pre=next=this;
	extra = 0;
	data = NULL;
}
template<class T>
list<T>::Node(const Node &other)
{
	pre=next=this;
	extra = other.extra;
	data = new T(*other.data);
}
template<class T>
class deque {

	typedef pair<T,void*> Data;
	typedef typename list<Data>::Node Node;
	typedef typename list<Node*>::Node BNode;

	list<Node*>blocks;
	list<Data> data;
	int history;

	void balanced()
	{
		int sqn = sqrt(data.SIZE),opn = 0;
		if(sqn < 10) sqn = 10;
		if( history < sqn )
			return;
		for(BNode *l = blocks.BEGIN;l!=blocks.END && opn < sqn;)
		if( l->extra > 2*sqn ){//split
			if(opn+sqn > sqn)
				{l=l->next;continue;}
			opn += sqn;
			int cot = l->extra/2;
			BNode *br = blocks.insert(l->pre, NULL);
			br->extra = cot;
			Node *r = *(l->data);
			for(;cot;--cot,r=r->next)
				r->data->second = br;
			*(l->data) = r;
			l = l->next;
		}else if( l->next != blocks.END && l->extra + l->next->extra <= sqn ){//merge
			int cot = min(l->extra,l->next->extra);
			if( opt + cot > sqn )
				{l=l->next;continue;}
			opn += cot;
			if( l->extra < l->next->extra )
			{
				l = l->next;
				l->extra += l->pre->extra;
				*(l->data) = *(l->pre->data);
				for(Node *r = *(l->pre->data); r->data->second==l->pre; r=r->next)
					r->data->second = l;
				blocks.remove(l->pre);
			}else{
				l->extra += l->next->extra;
				for(Node *r = *(l->next->data); r->data->second==l->next; r=r->next)
					r->data->second = l;
				blocks.remove(l->next);
			}
		}else l=l->next;
	}
	Node *insert( Node *r, const T &val )
	{
		history++;
		if(r->data==NULL)
		{
			r = data.insert(r->pre, Data(val, blocks.BEGIN));
			blocks.BEGIN->data = r;
			blocks.BEGIN->extra = 1;
		}else
		{
			((*BNode)(r->data->second))->extra++;
			r = data.insert(r->pre, Data(val, r->data->second));
		}
		balanced();
		return r;
	}
	Node *remove( Node *r )
	{
		BNode *br = (*BNode)(r->data->second);
		history++;
		if((--br->extra) == 0)
			br->data = NULL;
		r=r->next;
		data.remove(r->pre);
		balanced();
		return r;
	}
	size_t index( Node *r )
	{
		int cot=0,cot2=0;
		BNode *br = (*BNode)(r->data->second);
		while(br->data != r)
			r=r->pre,cot++;
		br = br->pre;
		for(;br!=blocks.END;br=br->pre)
			cot += br->extra;
		return cot;
	}
	Node *move( Node *r, int step )
	{
		if(!step)return r;
		BNode *br = (*BNode)(r->data->second);
		void *vr = r->data->second;
		if(step > 0)
		{
			//END's data == NULL ?
			for(; step && vr == r->data->second; --step)
				r = r->next;
			br = br->next;
			while( step >= br->extra )
			{
				step -= br->extra;
				br = br->next;
			}
			for(r=br->start;step; --step)
				r = r->next;
		}else{
			for(; step && vr == r->data->second; --step)
				r = r->pre;
			br = br->pre;
			while( step >= br->extra )
			{
				step -= br->extra;
				br = br->pre;
			}
			for(r=br->next->start->pre;step; --step)
				r = r->pre;
		}
		return r;
	}
	void copy( Node *er )
	{
		BNode *br = blocks.BEGIN;
		void *vr = NULL;
		Node *r = data.BEGIN;
		for(;er->extra!=-1;er=er->next)
		{
			if(er->data->second != vr)
			{
				br = blocks.insert( br, NULL );
				br->extra = ((BNode*)(vr))->extra;
			}
			r = insert( END, er->data );
			if(er->data->second != vr)
			{
				r->data->second = br;
				vr = er->data->second;
			}
		}
	}
public:
	class const_iterator;
	class iterator {
	private:
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
		 deque *ori;
		 Node *add;
		 iterator( deque *Origin, Node *Address )
		 :ori(Origin),add(Address){}
	public:
		iterator()
		{
			ori=NULL;
			add=NULL;
		}
		iterator( const iterator &other )
		{
			ori = other.ori;
			add = other.add;
		}
		/**
		 * return a new iterator which pointer n-next elements
		 *   even if there are not enough elements, the behaviour is **undefined**.
		 * as well as operator-
		 */
		iterator operator+(const int &n) const {
			//TODO
			return move(add,+n);
		}
		iterator operator-(const int &n) const {
			//TODO
			return move(add,-n);
		}
		// return th distance between two iterator,
		// if these two iterators points to different vectors, throw invaild_iterator.
		int operator-(const iterator &rhs) const {
			//TODO
			if(ori != rhs.ori) throw( invalid_iterator() );
			return index(add) - index(rhs.add);
		}
		iterator operator+=(const int &n) {
			//TODO
			add = move(add, +n);
			return *this;
		}
		iterator operator-=(const int &n) {
			//TODO
			add = move(add, -n);
			return *this;
		}
		/**
		 * TODO iter++
		 */
		iterator operator++(int)
		{
			if(add == data.END)throw(index_out_of_bound());
			iterator re(*this);
			add = add->next;
			return re;
		}
		/**
		 * TODO ++iter
		 */
		iterator& operator++()
		{
			if(add == data.END)throw(index_out_of_bound());
			add = add->next;
			return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int)
		{
			if(add == data.BEGIN)throw(index_out_of_bound());
			iterator re(*this);
			add = add->pre;
			return re;
		}
		/**
		 * TODO --iter
		 */
		iterator& operator--()
		{
			if(add == data.BEGIN)throw(index_out_of_bound());
			add = add->pre;
			return *this;
		}
		/**
		 * TODO *it
		 */
		T& operator*() const
		{ return add->data->first; }
		/**
		 * TODO it->field
		 */
		T* operator->() const noexcept
		{ return &(add->data->first); }
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		bool operator==(const iterator &rhs) const
		{ return add == rhs.add; }
		bool operator==(const const_iterator &rhs) const
		{ return add == rhs.add; }
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const
		{ return add != rhs.add; }
		bool operator!=(const const_iterator &rhs) const
		{ return add != rhs.add; }
	};
	class const_iterator {
		// it should has similar member method as iterator.
		//  and it should be able to construct from an iterator.
		private:
			// data members.
			const map* ori;
			const Node *add;
			const_iterator( const map* Origin, const Node *Address )
			:ori(Origin),add(Address)
		public:
			const_iterator()
			:ori(NULL),add(NULL){}
			const_iterator(const const_iterator &other)
			:ori(other.ori),add(other.add){}
			const_iterator(const iterator &other)
			:ori(other.ori),add(other.add){}
			// And other methods in iterator.
			// And other methods in iterator.
			// And other methods in iterator.
			/**
			 * return a new iterator which pointer n-next elements
			 *   even if there are not enough elements, the behaviour is **undefined**.
			 * as well as operator-
			 */
			iterator operator+(const int &n) const {
				//TODO
				return move(add,n);
			}
			iterator operator-(const int &n) const {
				//TODO
				return move(add,-n);
			}
			// return th distance between two iterator,
			// if these two iterators points to different vectors, throw invaild_iterator.
			int operator-(const const_iterator &rhs) const {
				//TODO
				if(ori != rhs.ori) throw( invalid_iterator() );
				return index(add) - index(rhs.add);
			}
			const_iterator operator+=(const int &n) {
				//TODO
				add = move(add, +n);
				return *this;
			}
			const_iterator operator-=(const int &n) {
				//TODO
				add = move(add, -n);
				return *this;
			}
			/**
			 * TODO iter++
			 */
			const_iterator operator++(int)
			{
				if(add == data.END)throw(index_out_of_bound());
				const_iterator re(*this);
				add = add->next;
				return re;
			}
			/**
			 * TODO ++iter
			 */
			const_iterator& operator++()
			{
				if(add == data.END)throw(index_out_of_bound());
				add = add->next;
				return *this;
			}
			/**
			 * TODO iter--
			 */
			const_iterator operator--(int)
			{
				if(add == data.BEGIN)throw(index_out_of_bound());
				const_iterator re(*this);
				add = add->pre;
				return re;
			}
			/**
			 * TODO --iter
			 */
			const_iterator& operator--()
			{
				if(add == data.BEGIN)throw(index_out_of_bound());
				add = add->pre;
				return *this;
			}
			/**
			 * TODO *it
			 */
			const T& operator*() const
			{ return add->data->first; }
			/**
			 * TODO it->field
			 */
			const T* operator->() const noexcept
			{ return &(data->data->first); }
			/**
			 * a operator to check whether two iterators are same (pointing to the same memory).
			 */
			bool operator==(const citerator &rhs) const
			{ return add == rhs.add; }
			bool operator==(const const_iterator &rhs) const
			{ return add == rhs.add; }
			/**
			 * some other operator for iterator.
			 */
			bool operator!=(const iterator &rhs) const
			{ return add != rhs.add; }
			bool operator!=(const const_iterator &rhs) const
			{ return add != rhs.add; }
	};
	/**
	 * TODO Constructors
	 */
	deque()
	{
		blocks.insert(blocks.BEGIN, NULL);
	}
	deque(const deque &other)
	{
		copy(other.BEGIN);
		history = other.history;
	}
	/**
	 * TODO Deconstructor
	 */
	~deque() {}
	/**
	 * TODO assignment operator
	 */
	deque &operator=(const deque &other)
	{
		if(other == this) return *this;
		data.clear();blocks.clear();
		copy(other.BEGIN);
		history = other.history;
		return *this;
	}
	/**
	 * access specified element with bounds checking
	 * throw index_out_of_bound if out of bound.
	 */
	T & at(const size_t &pos)
	{
		if(pos > data.SIZE)throw( index_out_of_bound() );
		Node *r = move(data.BEGIN,pos);
		return r->data->first;
	}
	const T & at(const size_t &pos) const
	{
		if(pos > data.SIZE)throw( index_out_of_bound() );
		Node *r = move(data.BEGIN,pos);
		return r->data->first;
	}
	T & operator[](const size_t &pos)
	{
		return at(pos);
	}
	const T & operator[](const size_t &pos) const
	{
		return at(pos);
	}
	/**
	 * access the first element
	 * throw container_is_empty when the container is empty.
	 */
	const T & front() const
	{
		if(empty()) throw(container_is_empty());
		return data.BEGIN->data->first;
	}
	/**
	 * access the last element
	 * throw container_is_empty when the container is empty.
	 */
	const T & back() const
	{
		if(empty()) throw(container_is_empty());
		return data.END->pre->data->first;
	}
	/**
	 * returns an iterator to the beginning.
	 */
	iterator begin()
	{ return iterator(this, data->BEGIN); }
	const_iterator cbegin() const
	{ return const_iterator(this, data->BEGIN); }
	/**
	 * returns an iterator to the end.
	 */
	iterator end()
	{ return iterator(this, data->END); }
	const_iterator cend() const
	{ return const_iterator(this, data->END); }
	/**
	 * checks whether the container is empty.
	 */
	bool empty() const
	{ return data.SIZE == 0; }
	/**
	 * returns the number of elements
	 */
	size_t size() const
	{ return data.SIZE; }
	/**
	 * clears the contents
	 */
	void clear()
	{ data.clear();blocks.clear(blocks.BEGIN->next);blocks.BEGIN->extra = 0; }
	/**
	 * inserts elements at the specified locat on in the container.
	 * inserts value before pos
	 * returns an iterator pointing to the inserted value
	 *     throw if the iterator is invalid or it point to a wrong place.
	 */
	iterator insert(iterator pos, const T &value)
	{
		if( pos.ori != this )throw( invalid_iterator() );
		pos.add = insert( pos.add, value );
		return pos;
	}
	/**
	 * removes specified element at pos.
	 * removes the element at pos.
	 * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
	 * throw if the container is empty, the iterator is invalid or it points to a wrong place.
	 */
	iterator erase(iterator pos)
	{
		if(empty())throw( container_is_empty() );
		if( pos.ori != this )throw( invalid_iterator() );
		if( pos.add == data.END )throw( invalid_iterator() );
		iterator re( this, pos.add->next );
		remove( pos.add );
		return re;
	}
	/**
	 * adds an element to the end
	 */
	void push_back(const T &value)
	{ insert( data.END, value ); }
	/**
	 * removes the last element
	 *     throw when the container is empty.
	 */
	void pop_back()
	{
		if(empty())throw( container_is_empty() );
		remove( data.END->pre );
	}
	/**
	 * inserts an element to the beginning.
	 */
	void push_front(const T &value)
	{ insert( data.BEGIN, value ); }
	/**
	 * removes the first element.
	 *     throw when the container is empty.
	 */
	void pop_front()
	{
		if(empty())throw( container_is_empty() );
		remove( data.BEGIN );
	}
};

}

#endif
