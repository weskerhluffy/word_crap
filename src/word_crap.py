# your code goes here
from heapq import heapify, heappush, heappop
from collections import deque

class priority_dict(dict):
    """Dictionary that can be used as a priority queue.

    Keys of the dictionary are items to be put into the queue, and values
    are their respective priorities. All dictionary methods work as expected.
    The advantage over a standard heapq-based priority queue is
    that priorities of items can be efficiently updated (amortized O(1))
    using code as 'thedict[item] = new_priority.'

    The 'smallest' method can be used to return the object with lowest
    priority, and 'pop_smallest' also removes it.

    The 'sorted_iter' method provides a destructive sorted iterator.
    """
    
    def __init__(self, *args, **kwargs):
        super(priority_dict, self).__init__(*args, **kwargs)
        self._rebuild_heap()

    def _rebuild_heap(self):
        self._heap = [(v, k) for k, v in self.items()]
        heapify(self._heap)

    def smallest(self):
        """Return the item with the lowest priority.

        Raises IndexError if the object is empty.
        """
        
        heap = self._heap
        v, k = heap[0]
        while k not in self or self[k] != v:
            heappop(heap)
            v, k = heap[0]
        return k

    def pop_smallest(self):
        """Return the item with the lowest priority and remove it.

        Raises IndexError if the object is empty.
        """
        
        heap = self._heap
        v, k = heappop(heap)
        while k not in self or self[k] != v:
            v, k = heappop(heap)
        del self[k]
        return k

    def __setitem__(self, key, val):
        # We are not going to remove the previous value from the heap,
        # since this would have a cost O(n).
        
        super(priority_dict, self).__setitem__(key, val)
        
        if len(self._heap) < 2 * len(self):
            heappush(self._heap, (val, key))
        else:
            # When the heap grows larger than 2 * len(self), we rebuild it
            # from scratch to avoid wasting too much memory.
            self._rebuild_heap()

    def setdefault(self, key, val):
        if key not in self:
            self[key] = val
            return val
        return self[key]

    def update(self, *args, **kwargs):
        # Reimplementing dict.update is tricky -- see e.g.
        # http://mail.python.org/pipermail/python-ideas/2007-May/000744.html
        # We just rebuild the heap from scratch after passing to super.
        
        super(priority_dict, self).update(*args, **kwargs)
        self._rebuild_heap()

    def sorted_iter(self):
        """Sorted iterator of the priority dictionary items.

        Beware: this will destroy elements as they are returned.
        """
        
        while self:
            yield self.pop_smallest()
            
class window_counter_queue():
	def __init__(self,cap):
		self.cap=cap
		self.count_queue=priority_dict()
		self.window_queue=deque()
		self.num_elems=0
	
	def add(self,elem):
		if self.num_elems>=self.cap:
			tail=self.window_queue.pop()
			self.count_queue[tail]=(self.count_queue[tail][0]+1,tail)
		self.window_queue.appendleft(elem)
		if elem not in self.count_queue:
			self.count_queue[elem]=(0,elem)
		self.count_queue[elem]=(self.count_queue[elem][0]-1,elem)
		self.num_elems+=1
#		print("despuesde anadir {} kedo {}".format(elem,self.count_queue))
	def top(self):
		r=[]
		if self.num_elems:
			r=self.count_queue[self.count_queue.smallest()]
		return r

t=int(input())
for i in range(t):
	n,k=[int(x) for x in input().strip().split(" ")]
	wcq=window_counter_queue(k)
	print("Case {}:".format(i+1))
	for _ in range(n):
		w=input().strip()
		wcq.add(w)
		r=wcq.top()
		print("{} {}".format(r[1],r[0]*-1))

