# Assembly Line Simulation Project

## Overview

This project involves creating a C++ assembly line simulation using Object-Oriented Programming (OOP) principles. The simulation models an assembly line with multiple stations that work together to process customer orders for various products. The project is structured into three milestones, progressively building the simulation's functionality.

![210157518-bbf19d92-bcfc-4d58-a2e6-a8683368d0f6](https://github.com/HenryLuong8888/-CPP-Assembly-Line/assets/113555331/dc1c1c2a-9d62-4858-8ad2-2f3eddf296f1)


The assembly line in the solution consists of a set of workstations each of which holds a set of stock items, which are specific to the station. A line 
manager moves customer orders along the line filling the orders at each station, as requested. Each customer order consists of a list of items that need to 
be filled. Each station processes a queue of orders by filling the next order in the queue if that order requests the station's item and that item is in 
stock. The line manager keeps moving the customer orders from station to station until all orders have been processed. Any station that has used all the 
items in stock cannot fill any more orders. At the end of the line orders are either completed or incomplete due to a lack of inventory at one or more 
stations. The simulator lists the completed orders and those that are incomplete once the line manager has finished processing all orders.

The solution that can be brought by the assembly line simulation project is the ability to simulate and analyze the functioning of an 
assembly line. By simulating the assembly line, We can study and understand the various processes and activities that take place at each station, as well 
as how the line manager coordinates the movement of orders and manages the filling of orders at each station.

In addition, the simulation can help to identify potential bottlenecks or inefficiencies in the assembly line, and to explore ways to optimize the 
line's performance. This could involve identifying ways to reduce the time it takes to fill orders at each station, improving the flow of orders through 
the line, or identifying ways to reduce the number of incomplete orders.

Overall, the assembly line simulation project can provide valuable insights and knowledge about the functioning and optimization of an assembly line, which 
can be useful for improving the efficiency and effectiveness of manufacturing or production processes in various industries.


## Milestone 1

Milestone 1 focuses on implementing and testing the `Utilities` and `Station` classes. The `Utilities` class assists in parsing input files and tokenizing strings. On the other hand, the `Station` class manages station-related information, such as items and customer order processing.

## Milestone 2

Milestone 2 introduces the `CustomerOrder` module, handling customer orders and their items. The `CustomerOrder` class oversees the movement of orders along the assembly line, ensuring they are filled by various stations. Additionally, the `Workstation` class, representing active stations, is implemented to fill customer orders and progress them to the next station.

## Milestone 3

The final milestone focuses on the `LineManager` module. The `LineManager` class configures the assembly line, manages order movement through stations, and handles the completion or incompleteness of orders. The simulation showcases the step-by-step processing of orders and station interactions.

## Key Concepts

- Object-Oriented Programming (OOP)
- Dynamic memory allocation
- Customer order management
- Station interactions
- Efficient workflow modeling
