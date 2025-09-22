# Movable Components

This project is a dynamic application built with Qt and QML that demonstrates modern C++ and QML best practices for creating a responsive user interface with a decoupled backend. It features animated, data-driven components whose behavior is controlled by a C++ backend.

---

### Technical Details

The application's technical stack includes:

* **Qt 5.14+**: The core framework for C++ and QML development.
* **QML (Qt Modeling Language)**: Used for building the declarative, dynamic user interface.
* **C++17**: For the application's business logic, including data generation and state management.
* **JSON**: Used for external configuration of both C++ data sources and QML component properties.
* **Qt Resource System (`.qrc`)**: The configuration and QML files are embedded directly into the executable, simplifying deployment.

---

### Architecture and Design

The project's architecture follows a **Model-View-Controller (MVC)**-like pattern, which separates the data, UI, and business logic.

* **View (QML)**: The `main.qml` file serves as the view. It declaratively defines the user interface, including the rectangles, their colors, and their animations. It observes the `MainController` for data changes but does not contain the business logic.
* **Model (C++ and JSON)**: The data is stored in JSON files, which act as the model. The C++ `DataGenerator` class is a thin wrapper that reads this data and emits updates.
* **Controller (C++)**: The `MainController` class acts as the central controller. It reads the JSON configuration files, instantiates `DataGenerator` objects, and exposes them to QML. It also manages the application's state, such as pausing data updates when a component moves to a specific area.

### Design Patterns

The project incorporates key design patterns:

* **Observer Pattern**: Implemented through Qt's Meta-Object System. The C++ `DataGenerator` (`Subject`) notifies the QML `Text` element (`Observer`) when its `value` property changes using `Q_PROPERTY` and a `NOTIFY` signal.
* **Singleton Pattern (Implied)**: While not a strict singleton, the `MainController` is instantiated once in `main.cpp` and exposed globally to QML, functioning as a single point of control.
* **Dependency Injection**: The `MainController` is initialized with the paths to the configuration files, making it a flexible and testable component.

---

### Build and Run Instructions

#### 1. Build the project using Qt Creator

1.  Open the project's `.pro` file in Qt Creator.
2.  In the **Projects** mode, select your desired **Build & Run Kit** to configure the compiler and Qt version.
3.  Click the **Build** button (the hammer icon) or press **Ctrl + B** to compile the project.

#### 2. Build the project from the command line

1.  Open a terminal and navigate to the project's root directory.
2.  Run `qmake` to generate the `Makefile`.
    ```bash
    qmake
    ```
3.  Run `make` to compile the source code and build the executable.
    ```bash
    make
    ```

#### 3. Run the application

The executable will be located in your build directory. Run it from your terminal or directly from Qt Creator.

```bash
./MovableComponents

