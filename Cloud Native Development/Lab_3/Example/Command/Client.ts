import {Invoker} from './Invoker';
import {Command1} from './Command';
import {Command2} from './Command';

var invoker = new Invoker();

var command1 = new Command1();
invoker.setCommand(command1);
invoker.executeCommand();

var command2 = new Command2();
invoker.setCommand(command2);
invoker.executeCommand();