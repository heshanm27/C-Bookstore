#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std; 

struct Book {
    string title{};
    string author{};
    float price{};
    int quantity{};
};

struct Order {
    int orderId{};
    string bookTitle;
    int quantity{};
    float totalPrice{};
};

vector<Book> books;
vector<Order> orders;


int getOrderCount() {
	string filePath = "./data/orders.txt";
	ifstream file(filePath);

    if (!file.is_open()) {
		std::cerr << "Error opening file: " << filePath << std::endl;
		return 0;
	}

	int count = 0;
	std::string line;
    while (getline(file, line)) {
		count++;
	}

	file.close();
	return count;
}
bool authenticateUser(const string& username, const string& password);
void ManageBooks();
void ManageOrders();
void addBook();
void viewBooks();
Book searchBooks();
Order searchOrders();
void prepareQuotation();
void printQuotations();
void viewOrders();
void addDiscount();




int main() {
    int choice;
    bool logOut = false;
    string username;
    string password;
    
   while (!logOut)
    {

        cout << "----------------------------------------------Bookshop---------------------------------------------------------\n\n";
        cout << "ENTER YOUR LOGIN DETAILS\n\n";
        cout << "\nENTER USERNAME : ";
        cin >> username;
        cout << "\nENTER PASSWORD : ";
        cin >> password;
        if (authenticateUser(username, password))
        {
            do {
                cout << "1. Manage Books\n";
                cout << "2. Manage orders \n";
                cout << "3. Logout\n";
                cout << "4. Exit\n";
                cout << "Enter your choice number: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    ManageBooks();
                    break;
                case 2:
                    ManageOrders();
                    break;
                case 3:
                    cout << "Logging out\n";
                    break;
                case 4:
                    logOut = true;
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                }
            } while (choice != 4 && choice != 3);

        }
        else
        {
            cout << "INVALID USERNAME OR PASSWORD !!!" << endl << endl;
        }

    }
    cout << "\n\nExiting...";
 
    return 0;
}


// Authenticate user function
bool authenticateUser(const string& username, const string& password) {
    string filePath = "./data/user.txt";
    ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return false;
    }

    std::string line;
    while (getline(file, line)) {
        // Create an input string stream from line
        istringstream readedStringStream(line);

        string storedUsername, storedPassword;

        // Use getline with ',' as delimiter to split the line
        getline(readedStringStream, storedUsername, ',');
        getline(readedStringStream, storedPassword, ',');

        if (username == storedUsername && password == storedPassword) {
            cout << "Login successful" << endl;
            return true;
        }
    }

    file.close();
    cout << "Login unsuccessful" << endl;
    return false; // No match found
}

// Manage Books Function
void ManageBooks(){

    int choice;
    do {
        cout << "1. View Books\n";
        cout << "2. Add Books \n";
        cout << "3. Search Books\n";
        cout << "4. Back\n";
        cout << "Enter your choice number: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewBooks();
            break;
        case 2:
            addBook();
            break;
        case 3:
           searchBooks();
            break;
        case 4:
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

}

// Manage Orders Function
void ManageOrders(){
    int choice;
    do {
        cout << "1. View Order\n";
        cout << "2. Prepare Quotations\n";
        cout << "3. Add Discount\n";
        cout << "4. Print Quotations\n";
        cout << "5. Back\n";
        cout << "Enter your choice number: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewOrders();
            break;
        case 2:
           prepareQuotation();
            break;
        case 3:
            addDiscount();
            break;
		case 4:
            printQuotations();
            break;
        case 5:
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}



// View Book Function
void viewBooks() { 

    string filePath = "./data/books.txt";
    ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }
    std::string line;
    while (getline(file, line)) {
        // Create an input string stream from line
        istringstream readedStringStream(line);

        string title, author;
        float price;
        int quantity;


        // Use getline with ',' as delimiter to split the line
        std::getline(readedStringStream, title, ',');
        std::getline(readedStringStream, author, ',');
        readedStringStream >> price;  // Assuming price is a floating-point number
        readedStringStream.ignore();   // Ignore the comma
        readedStringStream >> quantity; // Assuming quantity is an integer

        // Now you can use the extracted values (title, author, price, quantity) as needed
        std::cout << "Title: " << title << ", Author: " << author
            << ", Price: " << price << ", Quantity: " << quantity << std::endl;

    }

    file.close();
}

//add book function
void addBook() {
    Book book;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, book.title);
    cout << "Enter book author: ";
    getline(cin, book.author);
    cout << "Enter book price: ";
    cin >> book.price;
    cout << "Enter quantity in stock: ";
    cin >> book.quantity;
    books.push_back(book);

    string filePath = "./data/books.txt"; // Corrected file path

    // Open the file for appending
    ofstream file(filePath, ios::app);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl; // Corrected error message
        return;
    }

    // Write the book data to the file with comma-separated values
    file  << book.title << "," << book.author << "," << book.price << "," << book.quantity << endl;
    

    file.close();
}

// Search Book Function
Book searchBooks(){

    string bookTitle;
	cout << "Enter book title: ";
	cin.ignore();
	getline(cin, bookTitle);

    string filePath = "./data/books.txt";
    ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }
    std::string line;
    while (getline(file, line)) {
        // Create an input string stream from line
        istringstream readedStringStream(line);

        string title, author;
        float price;
        int quantity;


        // Use getline with ',' as delimiter to split the line
        std::getline(readedStringStream, title, ',');
        std::getline(readedStringStream, author, ',');
        readedStringStream >> price;  // Assuming price is a floating-point number
        readedStringStream.ignore();   // Ignore the comma
        readedStringStream >> quantity; // Assuming quantity is an integer

        if (title == bookTitle) {
			std::cout << "Title: " << title << ", Author: " << author
			<< ", Price: " << price << ", Quantity: " << quantity << std::endl;
            Book book = { title, author, price, quantity };
			return book;
		}

    }

    file.close();

	cout << "Book not found." << endl;  

}

//view orders function
void viewOrders() {
    string filePath = "./data/orders.txt";
	ifstream file(filePath);

    if (!file.is_open()) {
		std::cerr << "Error opening file: " << filePath << std::endl;
	}
	std::string line;
    while (getline(file, line)) {
		// Create an input string stream from line
		istringstream readedStringStream(line);

		string bookTitle;
		int quantity,orderId;
		float totalPrice;

     
        readedStringStream >> orderId;
        readedStringStream.ignore();   
        getline(readedStringStream, bookTitle, ','); 
        readedStringStream >> quantity;  
        readedStringStream.ignore();  
        readedStringStream >> totalPrice; 

        // The extracted values (title, author, price, quantity) as needed
        std::cout << "Order ID: " << orderId << ", Book Title: " << bookTitle
			<< ", Quantity: " << quantity << ", Total Price: " << totalPrice << std::endl;
   
    }

}

//add order discount function
void addDiscount() {

    Order order = searchOrders();

    // Check if the order was found
    if (order.orderId == 0 || order.bookTitle.empty()) {
        cout << "Order not found. Cannot apply discount." << endl;
        return;
    }

    float percentage;
    cout << "Enter Order discount percentage: ";
    cin >> percentage;

    float discount = order.totalPrice * percentage / 100;
    float totalPrice = order.totalPrice - discount;

    cout << "Order ID: " << order.orderId << endl;
    cout << "Book Title: " << order.bookTitle << endl;
    cout << "Quantity: " << order.quantity << endl;
    cout << "Total Price: " << order.totalPrice << endl;
    cout << "Discount: " << discount << endl;
    cout << "Total Price after discount: " << totalPrice << endl;

    // Update the existing order in the file
    string filePath = "./data/orders.txt";
    ifstream fileRead(filePath);
    ofstream fileWrite("./data/orders_temp.txt"); // Temporary file to write modified data

    if (!fileRead.is_open() || !fileWrite.is_open()) {
        cerr << "Error opening files for reading/writing." << endl;
        return;
    }

    string line;
    while (getline(fileRead, line)) {
        // Create an input string stream from line
        istringstream readedStringStream(line);

        string bookTitle;
        int quantity, orderId;
        float readtotalPrice;

        readedStringStream >> orderId;
        readedStringStream.ignore();
        getline(readedStringStream, bookTitle, ',');
        readedStringStream >> quantity;
        readedStringStream.ignore();
        readedStringStream >> readtotalPrice;

        if (orderId == order.orderId) {
            fileWrite << order.orderId << "," << order.bookTitle << "," << quantity << "," << totalPrice << endl;
        }
        else {
            fileWrite << line << endl;
        }
    }

    fileRead.close();
    fileWrite.close();

    // Replace the original file with the modified data
    remove(filePath.c_str());
    rename("./data/orders_temp.txt", filePath.c_str());

    cout << "Order updated successfully." << endl;
}
void prepareQuotation() {  // Prepare Quotation function
    Book book = searchBooks();
    Order order;
    order.orderId = getOrderCount() + 1;
    order.bookTitle = book.title;
    cout << "Enter quantity: ";
    cin >> order.quantity;
    order.totalPrice = book.price * order.quantity;

    cout << "Order ID: " << order.orderId << endl;
    cout << "Book Title: " << order.bookTitle << endl;
    cout << "Quantity: " << order.quantity << endl;
    cout << "Total Price: " << order.totalPrice << endl;



    string filePath = "./data/orders.txt";
    ofstream file(filePath,ios::app);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }

        file << order.orderId << "," << order.bookTitle << "," << order.quantity << "," << order.totalPrice << endl;


    file.close();
}

void printQuotations() {   // print quotation Function
     
    string filePath = "./data/orders.txt";
	ifstream file(filePath);

    if (!file.is_open()) {
		std::cerr << "Error opening file: " << filePath << std::endl;
	}

 
	std::string line;
    while (getline(file, line)) {
		// Create an input string stream from line
		istringstream readedStringStream(line);

		string bookTitle;
		int quantity,orderId;
		float totalPrice;

	 
		readedStringStream >> orderId; 
		readedStringStream.ignore();    
		getline(readedStringStream, bookTitle, ','); 
		readedStringStream >> quantity;  
		readedStringStream.ignore();  
		readedStringStream >> totalPrice; 

	
        //write to file
        ofstream fileWrite("./data/quotations.txt", ios::app);
        fileWrite << "Order ID: " << orderId << ", Book Title: " << bookTitle
            << ", Quantity: " << quantity << ", Total Price: " << totalPrice << std::endl;

        cout << "Order ID: " << orderId << ", Book Title: " << bookTitle
            << ", Quantity: " << quantity << ", Total Price: " << totalPrice << std::endl;
        
        fileWrite.close();
   
	}   

    file.close();

}

Order searchOrders() {
     // Search Order Function

	int orderId;
	cout << "Enter Order Id: ";
	cin >> orderId;

	string filePath = "./data/orders.txt";
	ifstream file(filePath);

    if (!file.is_open()) {
		std::cerr << "Error opening file: " << filePath << std::endl;
	}
	std::string line;
    while (getline(file, line)) {
		// Create an input string stream from line
		istringstream readedStringStream(line);

		string bookTitle;
		int quantity,OrderID;
		float totalPrice;

        readedStringStream >> OrderID; 
        readedStringStream.ignore();
        getline(readedStringStream, bookTitle, ',');
        readedStringStream >> quantity;
        readedStringStream.ignore();
        readedStringStream >> totalPrice;

        if (OrderID == orderId) { 

            Order order = { OrderID,  bookTitle, quantity, totalPrice };
            return order;
        }
    }

    file.close();

    cout << "Order not found." << endl;
    return Order();
}

