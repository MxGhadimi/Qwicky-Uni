set(PROJECT_SOURCES
    main.cpp

    src/app/mainwindow.cpp
    src/app/customerdashboard.cpp
    src/app/admindashboard.cpp

    src/widgets/additem.cpp
    src/widgets/item.cpp
    src/widgets/showitem.cpp
    src/widgets/ingredient.cpp
    src/widgets/addorder.cpp
    src/widgets/customer.cpp
    src/widgets/showselected.cpp
    src/widgets/order.cpp
    src/widgets/orderitems.cpp
    src/widgets/showorder.cpp
    src/widgets/showcustomer.cpp

    src/utils/Ceasor.cpp
    src/utils/databasemanager.cpp
)

set(PROJECT_HEADERS
    src/include/mainwindow.h
    src/include/customerdashboard.h
    src/include/admindashboard.h

    src/include/item.h
    src/include/ingredient.h
    src/include/additem.h
    src/include/showitem.h

    src/include/customer.h
    src/include/showcustomer.h

    src/include/order.h
    src/include/addorder.h
    src/include/showselected.h
    src/include/orderitems.h
    src/include/showorder.h

    src/include/commonincludes.h
    src/include/Ceasor.h
    src/include/databasemanager.h
)
