COVID CALL CENTRE via THREADS and SYNCHRONIZATION

-------------------------------------------------

In this file we have use threads and semaphores in order to create a Covid help-centre call line.
With the help of synchronization we can detect that at which time is there an open line for
the caller to create an appointment with the operator.

The project asks us to implement semaphores and threads which as you can see we have properly done,
and as a sub-point, we have use it for the trivial part of our code and not for any of the minor
areas of the code.

To begin we can first start by calling 'make' to compile the code
We then generate an output file which if we run by typing ' ./output ' followed by a number,
the code runs.

If we run ' ./output 1 ' we are seeing what happens if there is only one caller at the moment.
Just like that if we are running ' ./output 100 ' we see what happens if there are 100 calls 
at that moment.

In this code, semaphores help us manage the calls, when there is one thread being called, 
the process gets locked on that thread till the other ones get free.

-------------------------------------------------

implementation ->
$ make
$ ./output 100

-------------------------------------------------

Enjoy running this code till upto 200 callers and see how this program manages to update
values, add and remove callers and manage appointments!
