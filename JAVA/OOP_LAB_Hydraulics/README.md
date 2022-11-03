Hydraulic System Simulation
===========================

Design and implement a program to manage the simulation of an hydraulic system.  
All the classes must belong to the package **hydraulic**.

R1. Elements and pipes
----------------------

A hydraulic system is composed of elements (of different types) connected to each other (through pipes that are not explicitly modeled in the system).

A system is represented by an object of class **HSystem** that allows adding new elements through the method **addElement()** that accepts as argument an object of class **Element** and adds it to the system components.

By means of method **getElements()** it is possible to get an array containing all and only the elements that compose the system.

R2. Simple elements
-------------------

The simple elements are represented by the classes **Source**, **Tap**, and **Sink**.

All elements have a name that can be read through the getter method **getName()**.  
It is possible to connect the output of an element to the input of another element by means of the method **connect()** that accepts as argument the element whose input should be connected to the output of the subject: _a.connect(b);_ connects the output of element _a_ to the input of element _b_.

The invocation of method connect on a _Sink_ object has no effect.

Given an element, it is possible to know to which other output element it is connected by means of the method **getOutput()** that returns an _Element_ object.

R3. Complex elements
--------------------

In addition to the simple elements described above, there are some complex elements. The "T" element, represented by class **Split**, allows splitting the input flow into two equal output flows. For this class, the **connect()** method accepts an additional argument specifying which output is being connected, such parameter may assume the values _0_ for the first output and _1_ for the second output.  
For this class, it is possible to know which elements are connected to the outputs, by means of the method **getOutputs()** that returns an array with the two connected elements.

R4. Simulation
--------------

Given a valid system, i.e. a tree with a source as the root and where each path ends with a sink, it is possible to compute flow and how it is split among the distinct paths.

The computation takes place into two phases: in the first phase the parameters of the elements belonging to the system are defined, in the second phase the actual simulation starts.

During the first setup phase it is possible to:

*   define the flow of a Source through the method **setFlow()** that accepts a number representing the cubic meters per hour.
*   set the opening of _Tap_s using the method **setOpen()** that accepts a boolean argument. When a tap is open the output flow is equal to the input flow, otherwise the output is zero.

For the T split the input flow is divided into two equal output flows (each a half of the input flow).

The **simulate()** method of class _HSystem_, performs the flow computations for each element in the system starting from each source (for the source, only the output flow, and for the sink just the input flow). This method requires as argument an object implementing the **SimulationObserver** interface, that provides a single method.

When, during simulation, the input and output flows are known for an element method **notifyFlow()** must be called on the observer passing the element type, the name, and the input and output flows; if any of the flows is not defined (e.g. for the _Source_ and _Sink_), the constant _NO\_FLOW_ can be used.

*   Hint: given an object, to find out if it is an instance of a specific class the operator _instanceof_ can be used.  
    E.g. _if( element instanceof Source )_.
*   Warning: you are not required to implement the interface _SimulationObserver_, you only need to use it; an example of implementation that simply prints to the console the notifications, is given in class _PrintingObserver_.



Hydraulic System Simulation - **Extended**
==========================================

Extend, inside class **HSystemExt** the [functions already implemented](Requirements.html) in class _HSystem_.

The class **HSystemExt** extends class _HSystem_.

R5. Multi-split
---------------

Class **Multisplit** represents an extension of class _Split_ that allows multiple outputs. The constructor accepts, in addition to the name, the number of outputs.

The method **connect()** accepts two arguments: the element to be connected and the output number to connect it to. Outputs are numbered starting from _0_.

To find out which elements are connected to the outputs of a multi-splice, method **getOutputs()** can be used; it returns an array of the connected elements. If no elements is connected to an output the corresponding item in the array is set to _null_.

In preparation for the simulation method **setProportions()** can be used; it accepts a series of _double_ values that define the proportion according to which the input flow is divided among the outputs.

*   Assume that the number of proportions passed to the method is equal to the number of outputs and that their sum is _1.0_.

R6. Visualization
-----------------

Method **layout()** in class _HSystemExt_ (warning: not _HSystem_) returns a string containing the layout of the system using ASCII characters and spacing.

For instance, a system composed of a _Source_, connected to a _Tab_, that is connected to a _Split_ whose outputs are connected to _Sink_s, would return a layout like the following one:

\[Src\]Source -> \[R\]Tap -> \[T\]Split +-> \[sink A\]Sink
                                  | 
                                  +-> \[sink B\]Sink

*   Remember that the system might be incomplete, i.e., some elements' outputs might not be connected to any element.

R7. Element removal
-------------------

Method **deleteElement()** of class **HSystemExt** deletes from the system a previously added element; the method takes as input parameter the name of element to be deleted.

If such element is not _Split_ or a _Multisplit_ having more than one output connected to other elements, no operation is performed and the method returns _false_.

Otherwise (_Split_ or _Multisplit_ with at most one output connected or any other element type), the element is removed from the system, and if the element to be removed is connected to other elements in input or output, connections must be modified appropriately so that the upstream element is connected to the downstream one. In this case the method returns _true_.

Taking the example from R5, the layout after deleting the _Tap_ should be like the following one:

\[Src\]Source -> \[T\]Split +-> \[sink A\]Sink
                        |
                        +-> \[sink B\]Sink

R8. Maximum flow rate and related alarms
----------------------------------------

The new class **ElementExt** extends the class **Element** adding a method **setMaxFlow()**, which takes as input parameter a real number, representing the maximum flow rate of an element. If an element takes in input a flow greater than its max flow rate, the element is in danger of breaking down. For **Source** objects, since they do not have any input, calls to the **setMaxFlow()** method should not have any effect.

The **HSystemExt** class contains an overloaded version of the **simulate** method, taking as parameter the boolean **enableMaxFlowCheck**: if the latter is true, the method should check also the maximum flow of elements, notifying an error if the element input flow is greater than its maximum flow rate. The overloaded **simulate** method takes in input also an object implementing the **SimulationObserverExt** interface, which extends the **SimulationObserver**, adding a method **notifyFlowError**, which can be used to notify the aforementioned maximum flow error, passing the element type, the name, the input flow and the maximum flow rate.

*   Hint: it is allowed to modify the **Source**, **Split**, **Tap** and **Sink** classes to make them extend the **ElementExt** class (since the latter in turn extends **Element**).
