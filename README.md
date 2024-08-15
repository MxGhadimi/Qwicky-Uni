<p align="center">
  <img src="./data/images/icons/iconqwicky.png" alt="Qwicky Logo" width="150" height="150">
</p>

# Qwicky-Uni
### A University Project - Restaurant Management App
Project of Dr. Shamsaee's: Advanced Programming (Sadjad University of Technology - 2024)

---
### Overview
Qwicky is a comprehensive restaurant management application designed to streamline food ordering and management processes. This project serves as a personal exploration in this field.

<p align="center">
  <img src="./diagrams/d1.png" alt="Qwicky UI Preview"> 
</p>

### Motivations
- Gain hands-on knowledge and experience with the Qt framework and CMake
- Explore SQLite for effective data handling
- Understand how project deployment works
- Learn version control and file structure
- Develop a real-world application that integrates database management with a user-friendly interface
- Learn about documentation and its importance
----
### Documentation
- [Documentation](https://masaroshi.github.io/Qwicky-Uni/index.html)
- <a href="diagrams/Qwicky.drawio" download>UML Diagram</a>

### User Stories
### - As a Restaurant Manager, I want to:
1. Manage the Menu
   - View a list of menu items
   - Add new menu items with details like photo, name, price, description, available days, and a list of ingredients
   - Edit existing menu items
   - Delete menu items
   - Search for menu items based on various criteria

2. Manage Orders
   - Create new orders
   - Edit existing orders
   - Cancel orders
   - Change the status of orders to "Paid" or "Pending"
   - View a list of all orders
   - Search for orders based on various criteria

3. Manage Customers
   - Add new customers with details like name, phone number, address, balance, and debt
   - Edit customer information
   - Delete customers
   - Search for customers based on various criteria

### - As an Item, I need to:
- have a photo, name, price, description, available days, and a list of ingredients
- be able to display my information

### - As an Order, I need to:
- have a date and time of the order
- know the payment status
- know whether the order is a takeaway or dine-in (if dine-in, which table) order
- know the customer who placed the order
- have a list of ordered items
- know the total price
- be able to display order information
