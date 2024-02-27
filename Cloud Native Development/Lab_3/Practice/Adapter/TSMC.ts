import {Wafer} from './Wafer';
import {APC} from './APC';
import {AnotherAPC} from './AnotherAPC';
import {ProcessTool} from './ProcessTool';


var apc = new APC();
var processTool_a = new ProcessTool('A');
var processTool_b = new ProcessTool('B');
var processTool_c = new ProcessTool('C');


var wafer1 = new Wafer('N12345.00');
var wafer2 = new Wafer('N54321.00');
var wafer3 = new Wafer('N11111.00');

apc.execute(wafer1, processTool_a);
apc.execute(wafer2, processTool_b);
apc.execute(wafer3, processTool_c);



//var anotherAPC = new AnotherAPC();
//anotherAPC.execute(wafer1, processTool_a);
//anotherAPC.execute(wafer2, processTool_b);