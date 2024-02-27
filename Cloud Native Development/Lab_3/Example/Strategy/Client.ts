import {Strategy} from './Strategy';
import {SomeStrategy} from './Strategy';
import {OtherStrategy} from './Strategy';
import {Context} from './Context';

var context = new Context();

var str = new SomeStrategy();
context.setStrategy(str);
context.doSomething('client data');

var str = new OtherStrategy();
context.setStrategy(str);
context.doSomething('client data');