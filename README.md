# cs251-prog1
//project 1 from cs251, emphasis on pure OOP solutions to implement a distribution system
PROGRAM #1
For Program #1, you will be creating an object oriented program that will support distributions of products that are not locally made. Develop a group of classes that can work together to provide products to consumers. To properly understand the overall problem, you should spend part of your design time on the web understanding distribution strategies. Here are some of the basic ideas:
• Think about how distribution takes place. Consider having multiple layers of distribution such as National distribution outlets and then Local distribution outlets. It is a perfect scenario for OOP, when one center gets low on goods, they can send a message to the next level up, always keeping the supply chain filled. Think about what classes would make sense to support this.
• There are various strategies with product distribution where depending on the nature of the product it may be in local distribution centers (e.g., with Amazon there are Prime products) or take longer because it is stored farther away. Some strategies are to have priority-based distribution. Others have categories (such as selective, intensive or exclusive distribution). What strategy makes sense to you?
• There may be a variety of different types of transportation methods that may be used during stages of delivery – a train or cargo ship might be used for one stage and a van used to get the goods to the store for sale.
To manage the scope of this project, the following are the minimum requirements:
1. Support at least two different layers of distribution centers (National and local for example)
2. Support a distribution strategy that allows for three different kinds of distribution (e.g., Prime, priority based, or by category: Selective, Intensive and Exclusive). These are to be of your own choice but may influence delivery speeds and overall availability.
3. Support two different types of transportation of goods.
4. There should be at least 3 functions for each class, besides constructors and destructors.
5. Every class that manages dynamic memory needs a default constructor, a copy constructor (week #2 topic 3) and a destructor.
6. At least one single inheritance hierarchy is required using public derivation
The main point of this assignment is to make the development simpler through the use of OO techniques. Therefore, first make a plan of what kind of distribution you are going to support. Then, break it down into a series of classes and create them independent of the entire problem. Push up the common elements into a common base class; this is the important part! And lastly, avoid classes with only setters and getters with the exception of a node class! Keep classes small and functions small. A large class or function means that the problem has not yet been broken down into its basic components (objects).

REQUIRED DATA STRUCTURES
All repetitive data structure algorithms must be implemented using recursion in CS202. Implementation of the data structures requires full support of insert, removal, display, retrieval, and remove-all.
1. You will need one data structure to handle the products at a distribution center by category. An array of categories which each element has a linear linked list of the products of that category.
2. You will need a data structure to help with the prioritization of products that need to be ordered to avoid over traversal. This data structure can be of your choice. Pick what you think is best for run time efficiency.
3. Lastly, you will want a linear linked list for each product to map its path through the system (so you can trace where it started and where it is today). You will need one of these for every product!
4. Nodes must be implemented as a class (not a struct); no public data is allowed
