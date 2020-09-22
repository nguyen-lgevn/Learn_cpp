#include <iostream>
// Creator patterns
#include "01_creational_patterns/abstract_factory/HelloWorldAbstractFactory.h"
#include "01_creational_patterns/builder/HelloWorldBuilder.h"
#include "01_creational_patterns/factory_method/HelloWorldFactoryMethod.h"
#include "01_creational_patterns/object_pool/HelloWorldObjectPool.h"
#include "01_creational_patterns/prototype/HelloWorldPrototype.h"
#include "01_creational_patterns/singleton/HelloWorldSingleton.h"
// Structural patterns
#include "02_structural_patterns/adapter/HelloWorldAdapter.h"
#include "02_structural_patterns/bridge/HelloWorldBridge.h"
#include "02_structural_patterns/composite/HelloWorldComposite.h"
#include "02_structural_patterns/decorator/HelloWorldDecorator.h"
#include "02_structural_patterns/facade/HelloWorldFacade.h"
#include "02_structural_patterns/flyweight/HelloWorldFlyweight.h"
#include "02_structural_patterns/proxy/HelloWorldProxy.h"
// Behavioral patterns
#include "03_behavioral_patterns/chain_responsibility/HelloWorldChainResponsibility.h"
#include "03_behavioral_patterns/command/HelloWorldCommand.h"
#include "03_behavioral_patterns/interpreter/HelloWorldInterpreter.h"
#include "03_behavioral_patterns/iterator/HelloWorldIterator.h"
#include "03_behavioral_patterns/mediator/HelloWorldMediator.h"
#include "03_behavioral_patterns/memento/HelloWorldMemento.h"
#include "03_behavioral_patterns/observer/HelloWorldObserver.h"
#include "03_behavioral_patterns/state/HelloWorldState.h"
#include "03_behavioral_patterns/strategy/HelloWorldStrategy.h"
#include "03_behavioral_patterns/template_method/HelloWorldTemplateMethod.h"
#include "03_behavioral_patterns/visitor/HelloWorldVisitor.h"
using namespace design_patterns;

int main(int argc, char* argv[])
{
    std::cout << "============================================================" << std::endl;
    std::cout << "========================  Design patterns ==================" << std::endl;
    std::cout << "============================================================" << std::endl;

    std::cout << "=========================     Abstract Factory  ============" << std::endl;
    HelloWorldAbstractFactory helloWorldAbstractFactory;
    std::unique_ptr<HelloWorldAbstractFactoryObject> helloWorldAbstractFactoryObj = helloWorldAbstractFactory.createInstance();
    helloWorldAbstractFactoryObj->sayHello();

    std::cout << "=========================     Builder   ====================" << std::endl;
    HelloWorldBuilder helloWorldBuilder;
    helloWorldBuilder.construct("Builder");
    helloWorldBuilder.sayHello();

    std::cout << "=========================     Factory Method   =============" << std::endl;
    FactoryHelloWorld factoryHelloWorld;
    std::unique_ptr<IHelloWorld> helloWorldFactoryMethod = factoryHelloWorld.createHelloWorld();
    helloWorldFactoryMethod->sayHello();

    std::cout << "=========================     Object Pool ==================" << std::endl;
    std::unique_ptr<HelloWorldResource> helloWorldRes = std::move(HelloWorldObjectPool::getInstance().getResource());
    helloWorldRes->setHelloWorld("Hello World Object Pool");
    helloWorldRes->sayHello();

    std::cout << "=========================     Prototype   ==================" << std::endl;
    std::unique_ptr<HelloWorldPrototype> helloWorldPrototype = HelloWorldPrototype::PROTOTYPE->clone();
    helloWorldPrototype->sayHello();

    std::cout << "=========================     Singleton   ==================" << std::endl;
    HelloWorldSingleton::getInstance().sayHello();

    std::cout << "=========================     Adapter     ==================" << std::endl;
    HelloWorldAdapter<HelloWorldDesignPatternAdapter> *helloWorldAdapter =
        new HelloWorldAdapter<HelloWorldDesignPatternAdapter>(new HelloWorldDesignPatternAdapter(),
                &HelloWorldDesignPatternAdapter::sayHelloWorldDesignPatternAdapter);
    helloWorldAdapter->sayHello();

    std::cout << "=========================     Bridge      ==================" << std::endl;
    HelloWorldBridge helloWorldBridge;
    helloWorldBridge.sayHello();

    std::cout << "=========================     Composite   ==================" << std::endl;
    HelloWorldComposite helloWorldComposite;
    helloWorldComposite.add(std::make_shared<HelloWorldCompositeLeaf>());
    helloWorldComposite.sayHello();

    std::cout << "=========================     Decorator   ==================" << std::endl;
    DecoratorHelloWorld decoratorHelloWorld(std::make_shared<HelloWorldDecorator>());
    decoratorHelloWorld.sayHello();

    std::cout << "=========================     Facade      ==================" << std::endl;
    HelloWorldFacade helloWorldFacade;
    helloWorldFacade.sayHello();

    std::cout << "=========================     Flyweight   ==================" << std::endl;
    HelloWorldFlyweightFactory helloWorldFlyweightFactory;
    std::shared_ptr<IHelloWorld> flyweight = helloWorldFlyweightFactory.getHelloWorld("Hello World Flyweight");
    flyweight->sayHello();

    std::cout << "=========================     Proxy       ==================" << std::endl;
    HelloWorldProxy helloWorldProxy;
    helloWorldProxy.sayHello();

    std::cout << "=========================     Chain of Responsibility ======" << std::endl;
    std::shared_ptr<HelloWorldFirstHandler> firstHandler = std::make_shared<HelloWorldFirstHandler>();
    firstHandler->setNext(std::make_shared<HelloWorldSecondHandler>());
    firstHandler->sayHello();

    std::cout << "=========================     Command     ==================" << std::endl;
    HelloWorldCommand helloWorldCommand(std::make_shared<HelloWorldCommandObject>());
    helloWorldCommand.execute();

    std::cout << "=========================     Interpreter ==================" << std::endl;
    HelloWorldInterpreter helloWorldInterpreter;
    helloWorldInterpreter.interpreter("sayHello");

    std::cout << "=========================     Iterator    ==================" << std::endl;
    HelloWorldList<std::string> helloWorldList;
    helloWorldList.push("Hello World");
    helloWorldList.push("Iterator");
    Iterator<std::string> *helloWorldIterator = helloWorldList.createIterator();
    while (!helloWorldIterator->end())
    //for (helloWorldIterator->begin(); !helloWorldIterator->end(); helloWorldIterator->next())
    {
        std::cout << helloWorldIterator->currentItem() << " ";
        helloWorldIterator->next();
    }
    std::cout << std::endl;

    std::cout << "=========================     Mediator    ==================" << std::endl;
    std::shared_ptr<HelloWorldFirstObject> firstObj = std::make_shared<HelloWorldFirstObject>();
    std::shared_ptr<HelloWorldSecondObject> secondObj = std::make_shared<HelloWorldSecondObject>();
    HelloWorldMediator helloWorldMediator(firstObj, secondObj);
    helloWorldMediator.handleEvent();

    std::cout << "=========================     Memento     ==================" << std::endl;
    HelloWorldMementoOriginator helloWorldMementoOrig;
    helloWorldMementoOrig.setState("Hello World Memento");
    std::shared_ptr<HelloWorldMemento> helloWorldMemento = helloWorldMementoOrig.createMemento();
    helloWorldMementoOrig.setState("Hello World New Memento");
    helloWorldMementoOrig.restoreFromMemento(helloWorldMemento);
    helloWorldMementoOrig.sayHello();

    std::cout << "=========================     Null Object ==================" << std::endl;
    std::cout << "=========================     Observer    ==================" << std::endl;
    std::shared_ptr<HelloWorldObserverSubject> helloWorldObserverSubject = std::make_shared<HelloWorldObserverSubject>();
    std::shared_ptr<HelloWorldObserver> helloWorldObserver = std::make_shared<HelloWorldObserver>();
    helloWorldObserver->setSubject(helloWorldObserverSubject);
    helloWorldObserverSubject->setHelloWorld("Hello World Observer");

    std::cout << "=========================     State       ==================" << std::endl;
    std::shared_ptr<HelloWorldStateContext> helloWorldStateContext = std::make_shared<HelloWorldStateContext>();
    helloWorldStateContext->process()->process();
    helloWorldStateContext->sayHello();

    std::cout << "=========================     Strategy    ==================" << std::endl;
    HelloWorldStrategyContext helloWorldStrategyContext;
    helloWorldStrategyContext.setStrategy(std::make_shared<HelloWorldStrategy>());
    helloWorldStrategyContext.sayHello();

    std::cout << "=========================     Template Method    ===========" << std::endl;
    HelloWorldTemplateMethod helloWorldTemplateMethod;
    helloWorldTemplateMethod.sayHello();

    std::cout << "=========================     Visitor     ==================" << std::endl;
    HelloWorldVisitor helloWorldVisitor;
    helloWorldVisitor.visit(std::make_shared<HelloWorldElementHello>());
    helloWorldVisitor.visit(std::make_shared<HelloWorldElementVisitor>());
    return 0;
}
