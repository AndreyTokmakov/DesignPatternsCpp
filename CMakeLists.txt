cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(DesignPatterns)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -pthread")
set(PROJECT_VERSION 1.0.0.0)
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)

add_compile_options(-c -Wall -Wextra -O3 -std=c++2a)

# include all components
add_executable(DesignPatterns
    main.cpp
	AbstractFactory/AbstractFactory.h AbstractFactory/AbstractFactory.cpp
	Adapter/Adapter.h Adapter/Adapter.cpp Adapter/USBAdapter.cpp
	Adapter/BaseAdapter.cpp Adapter/GoodExample.cpp
	Bridge/Bridge.h Bridge/Bridge.cpp Bridge/DrawingBridge.cpp
	Builder/Builder.h Builder/Builder.cpp
	Builder/HtmlBuilder.cpp Builder/UserBuilder.cpp
	ChainOfResponsibility/ChainOfResponsibility.h ChainOfResponsibility/ChainOfResponsibility.cpp
	ChainOfResponsibility/Example2.cpp
	Command/Command.h Command/Command.cpp Command/Command_MethodPtr.cpp
	Composite/Composite.h Composite/Composite.cpp
	CopyAndSwap/CopyAndSwap.cpp CopyAndSwap/CopyAndSwap.h
    CRTP/CRTP.cpp CRTP/CRTP.h CRTP/ObjectCounter.cpp CRTP/ObjectCounter.h
    Decorator/Decorator.cpp Decorator/Decorator.h
	Decorator/ShapeDecorator.cpp Decorator/ShapeDecorator.h
    FabricMethod/FabricMethod.h FabricMethod/FabricMethod.cpp  FabricMethod/FabricMethod2.cpp
	Facade/Facade.cpp Facade/Facade.h
    Filter/Filter.cpp Filter/Filter.h
    Flyweight/Flyweight.cpp Flyweight/Flyweight.h Flyweight/IconFlyweight.cpp
    Interpreter/Interpreter.cpp Interpreter/Interpreter.h
	LazyInitialization/LazyInitialization.cpp LazyInitialization/LazyInitialization.h
    Mediator/Mediator.cpp Mediator/Mediator.h Mediator/ChatMediator.cpp
	Memento/Memento.cpp Memento/Memento.h
    Named_Parameter_Idiom/NamedParameter.cpp Named_Parameter_Idiom/NamedParameter.h
	ObjectPools/ObjectPoolsSimple.cpp  ObjectPools/ObjectPoolsExtended.cpp ObjectPools/ObjectPools.h
    Observer/Observer.cpp Observer/Observer.h
	Observer/ObserverBasic.cpp Observer/ObserverSubject.cpp
	Policy/Policy.cpp Policy/Policy.h
    Prototype/Prototype.cpp Prototype/Prototype.h
	Proxy/Document.cpp Proxy/CarProxy.cpp Proxy/Proxy.h Proxy/Subject.cpp
    RAII/RAII.cpp RAII/RAII.h
    Singleton/Singleton.cpp Singleton/Singleton.h
	ExecutorAdapter/ExecutorAdapter.cpp ExecutorAdapter/ExecutorAdapter.h
    State/State.cpp State/State.h
    Strategy/Strategy.cpp Strategy/Strategy.h
    TypeErasure/TypeErasure.cpp TypeErasure/TypeErasure.h
    TagDispatching/TagDispatching.cpp TagDispatching/TagDispatching.h
    Iterator/Iterator.cpp Iterator/Iterator.h Iterator/RangeIterator.cpp
	Visitor/Visitor.cpp Visitor/Visitor.h
	Visitor/StockVisitor.cpp Visitor/DynamicComponentsVisitor.cpp Visitor/CarVisitor.cpp
	VirtualConstructor/VirtualConstructor.cpp VirtualConstructor/VirtualConstructor.h
	TemplateMethod/TemplateMethod.cpp TemplateMethod/TemplateMethod.h
	TemplateMethod/TemplateMethod_ExampleTwo.cpp TemplateMethod/TemplateMethod_ExampleThree.cpp
)

TARGET_LINK_LIBRARIES(DesignPatterns pthread)