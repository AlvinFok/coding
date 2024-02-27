import {ConcreteCreatorA} from './Creator';
import {ConcreteCreatorB} from './Creator';

var creator = new ConcreteCreatorA();
var product = creator.createProduct();
product.doStuff();

var creator = new ConcreteCreatorB();
var product = creator.createProduct();
product.doStuff();