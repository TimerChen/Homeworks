#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"

template<class T>
void swap( T &a, T &b )
{ T c(a); a=b;b=c; }

template<class T>
T min(const T &a, const T &b){return a<b?a:b;}

namespace sjtu {

/**
 * a container like std::priority_queue which is a heap internal.
 * it should be based on the vector written by yourself.
 */
template<typename T, class Compare = std::less<T> >
class priority_queue {
private:
	struct Node
	{
		Node( Node *null=NULL );
		Node( const Node *a );
		~Node(){ delete data; }
		T *data;
		int npl;
		Node *ch[2],*nflag;
		void update()
		{ npl = min( ch[0]->npl, ch[1]->npl )+1; }
		void pushdown( Node *null )
		{
			if( nflag != null )
			{
				if(ch[0] == nflag) ch[0] = null;
				if(ch[1] == nflag) ch[1] = null;
				nflag = null;
			}
		}
	}*ROOT;
	Node null[1];
	int SIZE;

	Node *merge( Node *a, Node *b )
	{
		a->pushdown( null );
		b->pushdown( null );
		if(a==null)return b;
		if(b==null)return a;
		if( Compare()(*a->data, *b->data) ) swap(a,b);
		a->ch[1] = merge( a->ch[1], b );
		if(a->ch[0]->npl < a->ch[1]->npl) swap(a->ch[0], a->ch[1]);
		a->update();
		return a;
	}
	void copy( Node *&ro, const Node *oro )
	{
		if(oro == oro->nflag)return;
		ro = new Node(null);
		ro->data = new T(*oro->data);
		copy( ro->ch[0], oro->ch[0] );
		copy( ro->ch[1], oro->ch[1] );
	}
	void clear( Node *&ro )
	{
		ro->pushdown( null );
		if(ro==null)return;
		clear(ro->ch[0]);clear(ro->ch[1]);
		delete ro;
		ro = null;
	}
public:
	/**
	 * TODO constructors
	 */
	priority_queue() {
		null[0]=Node(null);null[0].npl=-1;
		SIZE = 0; ROOT = null;
	}
	priority_queue(const priority_queue &other)
	{
		null[0]=Node(null);null[0].npl=-1;
		ROOT = null;
		copy(ROOT, other.ROOT);
		SIZE = other.SIZE;
	}
	/**
	 * TODO deconstructor
	 */
	~priority_queue()
	{ clear(ROOT); }
	/**
	 * TODO Assignment operator
	 */
	priority_queue &operator=(const priority_queue &other)
	{
		if(&other == this)return *this;
		clear(ROOT); copy(ROOT, other.ROOT); SIZE = other.SIZE;
		return *this;
	}
	/**
	 * get the top of the queue.
	 * @return a reference of the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	const T & top() const {
		if( empty() )throw container_is_empty();
		return *ROOT->data;
	}
	/**
	 * TODO
	 * push new element to the priority queue.
	 */
	void push(const T &e) {
		Node *element = new Node(null);
		element->data = new T(e);
		ROOT = merge( ROOT, element );
		SIZE++;
	}
	/**
	 * TODO
	 * delete the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	void pop() {
		if(empty()) throw container_is_empty();
		Node *top = ROOT;
		ROOT = merge( ROOT->ch[0], ROOT->ch[1] );
		delete top;
		SIZE--;
	}
	/**
	 * return the number of the elements.
	 */
	size_t size() const {
		return SIZE;
	}
	/**
	 * check if the container has at least an element.
	 * @return true if it is empty, false if it has at least an element.
	 */
	bool empty() const {
		return SIZE == 0;
	}
	/**
	 * return a merged priority_queue with at least O(logn) complexity.
	 */
	priority_queue &merge(priority_queue &other) {
		if( &other == this )return *this;
		SIZE += other.SIZE;
		ROOT = merge( ROOT, other.ROOT );
		other.ROOT = other.null;
		other.SIZE = 0;
		return *this;
	}
	void clear()
	{
		clear(ROOT);
	}
};
template<typename T, class Compare >
priority_queue<T,Compare>::Node::Node( Node *null )
{
	data = NULL;
	npl = -1;
	nflag = ch[0] = ch[1] = null;
	if( this == null )npl = -1;
	else npl = 0;
};
template<typename T, class Compare >
priority_queue<T,Compare>::Node::Node( const Node *a )
{
	data = new T(*a->data);
	npl = a->npl;
	nflag = a->nflag;
	ch[0] = a->ch[0];
	ch[1] = a->ch[1];
}
}

#endif
