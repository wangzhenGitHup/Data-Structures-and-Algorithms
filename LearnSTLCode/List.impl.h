#pragma once

namespace SelfSTL
{
	namespace ListNode
	{
		template<class T>
		ListIterator<T>& ListIterator<T>::operator ++()
		{
			p = p->next;
			return *this;
		}

		template<class T>
		ListIterator<T> ListIterator<T>::operator ++(int)
		{
			auto res = *this;
			++*this;
			return res;
		}

		template<class T>
		ListIterator<T>& ListIterator<T>::operator --()
		{
			ptr_ = ptr_->prev;
			return *this;
		}

		template<class T>
		ListIterator<T> ListIterator<T>::operator --(int)
		{
			auto tmp = *this;
			--*this;
			return tmp;
		}

		template<class T>
		bool operator==(const ListIterator<T>& lhs, const ListIterator<T>& rhs)
		{
			return lhs.ptr_ == rhs.ptr_;
		}

		template<class T>
		bool operator !=(const ListIterator<T>& lhs, const ListIterator<T>& rhs)
		{
			return !(lhs == rhs);
		}

	}//end namespace ListNode

	template<class T>
	void List<T>::insert_aux(iterator position, size_type n, const T& val, std::true_type)
	{
		for (auto i = n; i != 0; --i)
		{
			position = insert(position, val);
		}
	}

	template<class T>
	template<class InputIterator>
	void List<T>::insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type)
	{
		for (--last; first != last; --last)
		{
			position = insert(position, *last);
		}

		insert(position, *last);
	}

	template<class T>
	typename List<T>::nodePtr List<T>::newNode(const T& val /* = T() */)
	{
		NodePtr tmp = NodeAllocator::allocates();
		NodeAllocator::construct(tmp, ListNode::Node<T>(val, nullptr, nullptr, this));
		return tmp;
	}

	template<class T>
	void List<T>::deleteNode(NodePtr p)
	{
		p->prev = p->next = nullptr;
		NodeAllocator::destroy(p);
		NodeAllocator::deallocate(p);
	}

	template<class T>
	void List<T>::ctorAux(size_type n, const value_type& val, std::true_type)
	{
		head_.ptr_ = newNode();
		tail_.ptr_ = head_.ptr_;
		while (n--)
		{
			push_back(val);
		}
	}

	template<class T>
	template<class InputIterator>
	void List<T>::ctorAux(InputIterator first, InputIterator last, std::false_type)
	{
		head_.ptr_ = newNode();
		tail_.ptr_ = head_.ptr_;
		for (; first != last; ++first)
		{
			push_back(*first);
		}
	}

	template<class T>
	typename List<T>::size_type List<T>::size()const
	{
		size_type len = 0;
		for (auto ptr = head_; ptr != tail_; ++ptr)
		{
			++len;
		}

		return len;
	}

	template<class T>
	List<T>::List()
	{
		head_.ptr_ = newNode();
		tail_.ptr_ = head_.ptr_;
	}

	template<class T>
	List<T>::List(size_type n, const value_type& val /* = value_type() */)
	{
		ctorAux(n, val, std::is_integral<value_type>());
	}

	template<class T>
	template<class InputIterator>
	List<T>::List(InputIterator first, InputIterator last)
	{
		ctorAux(first, last, std::is_integral<InputIterator>());
	}

	template<class T>
	List<T>::List(const List& list)
	{
		head_.ptr_ = newNode();
		tail_.ptr_ = head_.ptr_;
		for (auto node = list.head_.ptr_; node != list.tail_.ptr_; node = node->next)
		{
			push_back(node->data);
		}
	}

	template<class T>
	List<T>& List<T>::operator =(const List& list)
	{
		if (this != &list)
		{
			List(list).swap(*this);
		}

		return *this;
	}
	

	template<class T>
	List<T>::~List()
	{
		for (; head_ != tail_;)
		{
			auto tmp = head_++;
			NodeAllocator::destroy(tmp.ptr_);
			NodeAllocator::deallocate(tmp.ptr_);
		}

		NodeAllocator::deallocate(tail_.ptr_);
	}


	template<class T>
	void List<T>::push_front(const value_type& val)
	{
		insert(begin(), val);
	}

	template<class T>
	void List<T>::pop_front()
	{
		erase(begin());
	}

	template<class T>
	void List<T>::push_back(const value_type& val)
	{
		insert(end(), val);
	}

	template<class T>
	void List<T>::pop_back()
	{
		auto tmp = end();
		erase(--tmp);
	}

	template<class T>
	typename List<T>::iterator List<T>::insert(iterator position, const value_type& val)
	{
		auto node = newNode(val);
		auto prev = position.ptr_->prev;
		node->next = position.ptr_;
		node->prev = prev;
		prev->next = node;
		position.ptr_->prev = node;
		return iterator(node);
	}

	template<class T>
	void List<T>::insert(iterator position, size_type n, const value_type& val)
	{
		insert_aux(position, n, val, typename std::is_integral<InputIterator>::type());
	}

	template<class T>
	template<class InputIterator>
	void List<T>::insert(iterator position, InputIterator first, InputIterator last)
	{
		insert_aux(position, first, last, typename std::is_integral<InputIterator>::type());
	}

	template<class T>
	typename List<T>::iterator List<T>::erase(iterator position)
	{
		auto next_node = position.ptr_->next;
		auto prev_node = position.ptr_->prev;
		prev_node->next = next_node;
		next_node->prev = prev_node;

		deleteNode(position.ptr_);
		return iterator(next_node);
	}

	template<class T>
	typename List<T>::iterator List<T>::erase(iterator first, iterator last)
	{
		typename List<T>::iterator ret;
		for (; first != last;)
		{
			auto tmp = first++;
			ret = erase(tmp);
		}

		return ret;
	}

	template<class T>
	void List<T>::clear()
	{
		erase(begin(), end());
	}

	template<class T>
	typename List<T>::iterator List<T>::begin()
	{
		return head_;
	}

	template<class T>
	typename List<T>::iterator List<T>::end()
	{
		return tail_;
	}

	template<class T>
	typename List<T>::const_iterator List<T>::changeIteratorToConstIterator(iterator& it)const
	{
		using nodePtr = ListNode::Node<const T>*;
		auto tmp = (List<const T>*const)this;
		auto ptr = it.ptr_;
		ListNode::Node<const T>node(ptr->data, (nodePtr)(ptr->prev), (nodePtr)(ptr->next), tmp);
		return const_iterator(&node);
	}

	template<class T>
	typename List<T>::const_iterator List<T>::end()const
	{
		auto tmp = (List*const)this;
		return changeIteratorToConstIterator(tmp->tail_);
	}

	template<class T>
	typename List<T>::reverse_iterator List<T>::rbegin()
	{
		return reverse_iterator(tail_);
	}

	template<class T>
	typename List<T>::reverse_iterator List<T>::rend()
	{
		return reverse_iterator(head_);
	}

	template<class T>
	void List<T>::reverse()
	{
		if (empty() || head_.ptr_->next == tail_.ptr_)
		{
			return;
		}

		auto curNode = head_.ptr_;
		head_.ptr_ = tail_.ptr_->prev;
		head_.ptr_->prev = nullptr;

		do 
		{
			auto nextNode = curNode->next;
			curNode->next = head_.ptr_->next;
			head_.ptr_->next->prev = curNode;
			head_.ptr_->next = curNode;
			curNode->prev = head_.ptr_;
			curNode = nextNode;
		} while (curNode != head_.ptr_);
	}

	template<class T>
	void List<T>::remove(const value_type& val)
	{
		for (auto it = begin(); it != end();)
		{
			if (*it == val)
			{
				it = erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	template<class T>
	template<class Predicate>
	void List<T>::remove_if(Predicate pred)
	{
		for (auto it = begin(); it != end();)
		{
			if (pred(*it))
			{
				it = erase(it);
			}
			else
			{
				++it;
			}
		}
	}


	template<class T>
	void List<T>::swap(List& list)
	{
		SelfSTL::swap(head_.ptr_, list.head_.ptr_);
		SelfSTL::swap(tail_.ptr_, list.tail_.ptr_);
	}

	template<class T>
	void swap(List<T>& list1, List<T>& list2)
	{
		list1.swap(list2);
	}

	template<class T>
	void List<T>::unique()
	{
		NodePtr curNode = head_.ptr_;

		while (curNode != tail_.ptr_)
		{
			NodePtr nextNode = curNode->next;
			if (curNode->data == nextNode->data)
			{
				if (nextNode == tail_.ptr_)
				{
					curNode->next = nullptr;
					tail_.ptr_ = curNode;
				}
				else
				{
					curNode->next = nextNode->next;
					nextNode->next->prev = curNode;
				}

				deleteNode(nextNode);
			}
			else
			{
				curNode = nextNode;
			}
		}
	}

	template<class T>
	template<class BinaryPredicate>
	void List<T>::unique(BinaryPredicate pred)
	{
		NodePtr curNode = head_.ptr_;
		while (curNode != tail_.ptr_)
		{
			nodePtr nextNode = curNode->next;
			if (pred(curNode->data, nextNode->data))
			{
				if (nextNode == tail_.ptr_)
				{
					curNode->next = nullptr;
					tail_.ptr_ = curNode;
				}
				else
				{
					curNode->next = nextNode->next;
					nextNode->next->prev = curNode;
				}

				deleteNode(nextNode);
			}
			else
			{
				curNode = nextNode;
			}
		}
	}


	template<class T>
	void List<T>::splice(iterator position, List& list)
	{
		//insert(position, list.begin(), list.end());
		//list.head_.ptr_ = list.tail_.ptr_;
		if (!list.empty())
		{
			transfer(position, list.begin(), list.end());
		}
	}

	template<class T>
	void List<T>::splice(iterator position, List& list, iterator first, iterator last)
	{
		/*if (first.ptr_ == last.ptr_)
		{
			return;
		}

		auto tailNode = last.ptr_->prev;
		if (list.head_.ptr_ == first.ptr_)
		{
			list.head_.ptr_ = last.ptr_;
			list.head_.ptr_->prev = nullptr;
		}
		else
		{
			first.ptr_->prev->next = last.ptr_;
			last.ptr_->prev = first.ptr_->prev;
		}

		if (position.ptr_ == head_.ptr_)
		{
			first.ptr_->prev = nullptr;
			tailNode->next = head_.ptr_;
			head_.ptr_->prev = tailNode;
			head_.ptr_ = first.ptr_;
		}
		else
		{
			position.ptr_->prev->next = first.ptr_;
			first.ptr_->prev = position.ptr_->prev;
			tailNode->next = position.ptr_;
			position.ptr_->prev = tailNode;
		}*/

		if (first != last)
		{
			transfer(position, first, last);
		}
	}


	template<class T>
	void List<T>::splice(iterator position, List& list, iterator it)
	{
		/*auto next = it;
		splice(position, list, ++next);*/

		iterator tmp = it;
		++tmp;
		if (position == it || position == tmp)
		{
			return;
		}

		transfer(position, it, tmp);
	}

	template<class T>
	void List<T>::merge(List& list)
	{
		auto it1 = begin(), it2 = list.begin();
		while (it1 != end() && it2 != list.end())
		{
			if (*it1 <= *it2)
			{
				++it1;
			}
			else
			{
				auto temp = it2++;
				splice(it1, list, temp);
			}
		}

		if (it1 == end())
		{
			splice(it1, list, it2, list.end());
		}
	}

	template<class T>
	template<class Compare>
	void List<T>::merge(List& list, Compare comp)
	{
		auto it1 = begin();
		auto it2 = list.begin();
		while (it1 != end() && it2 != list.end())
		{
			if (comp(*it2, *it1))
			{
				auto tmp = it2++;
				splice(it1, list, tmp);
			}
			else
			{
				++it1;
			}
		}

		if (it1 == end())
		{
			splice(it1, list, it2, list.end());
		}
	}

	template<class T>
	bool operator==(const List<T>& lhs, const List<T>& rhs)
	{
		auto node1 = lhs.head_.ptr_;
		auto node2 = rhs.head_.ptr_;
		for (; node1 != lhs.tail_.ptr_ && node2 != rhs.tail_.ptr_; 
			node1 = node1->next, node2 = node2->next)
		{
			if (node1->data != node2->data)
			{
				break;
			}
		}

		if (node1 = lhs.tail_.ptr_ && node2 == rhs.tail_.ptr_)
		{
			return true;
		}

		return false;
	}


	template<class T>
	bool operator != (const List<T>& lhs, const List<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template<class T>
	void List<T>::sort()
	{
		sort(SelfSTL::less<T>());
	}

	template<class T>
	template<class Compare>
	void List<T>::sort(Compare comp)
	{
		if (empty() || head_.ptr_->next == tail_.ptr_)
		{
			return;
		}

		List carry;
		List counter[64];
		int fill = 0;
		while (!empty())
		{
			carry.splice(carry.begin(), *this, begin());
			int i = 0;
			while (i < fill && !counter[i].empty())
			{
				counter[i].merge(carry, comp);
				carry.swap(counter[i++]);
			}

			carry.swap(counter[i]);
			if (i == fill)
			{
				++fill;
			}
		}

		for (int i = 0; i != fill; ++i)
		{
			counter[i].merge(counter[i - 1], comp);
		}

		swap(counter[fill - 1]);
	}

	template<class T>
	void List<T>::transfer(iterator position, iterator first, iterator last)
	{
		if (position != last)
		{
			last.ptr_->prev->next = position.ptr_;
			first.ptr_->prev->next = last.ptr_;
			position.ptr_->prev->next = first.ptr_;
			NodePtr* tmp = position.ptr_->prev;
			position.ptr_->prev = last.ptr_->prev;
			last.ptr_->prev = first.ptr_->prev;
			first.ptr->prev = tmp;
		}
	}
}