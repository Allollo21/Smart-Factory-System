# Smart Manufacturing System

This project is a smart manufacturing system that uses a linked list of queues of stacks to manage the production process of different products. Each product has a sequence of steps that need to be performed in order to complete it. The system allows the user to add new products, process the next step for the current product, and display the product sequence.

## Installation

To install this project, you need to have a C++ compiler and an IDE that supports C++. Follow the steps below:

1. Download the source code from this repository.
2. Open the downloaded source code in your C++ compatible IDE.
3. Alternatively, you can use the command line to compile and run the project.

## Usage

To use this project, run the main file, and it will display a menu with the following options:

- **[1] Add A Product:** Enter the number of operations and the name of each operation for a new product. The product will be added to the end of the production line.
- **[2] Process Next Step:** Process the next step for the current product. The step will be removed from the product’s stack, and a message will be displayed. If the product has no more steps, it will be removed from the queue, and another message will be displayed. If there are no products in the production line, a message will indicate that.
- **[3] Display Product Sequence:** Display the product sequence in the production line. Each product will be shown with its stack of steps.
- **[0] Exit:** Exit the program.

Feel free to interact with the system using the provided menu options to manage and monitor the smart manufacturing process.

## Contributing

Contributions are welcome! If you have any suggestions or improvements, feel free to open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
