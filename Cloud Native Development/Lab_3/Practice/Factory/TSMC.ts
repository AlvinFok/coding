import {Wafer} from './Wafer';
import {APC} from './APC';
import {ProcessTool} from './ProcessTool';


var apc = new APC();
var processTool_a = new ProcessTool('A');
var processTool_b = new ProcessTool('B');

var wafer1 = new Wafer('N12345.00', 'Mobile Phone', 'ByProductStrategy');
var wafer2 = new Wafer('N54321.00', 'Personal Computer', 'ByProductStrategy');
var wafer3 = new Wafer('N11111.00', 'NoteBook', 'ByProductStrategy');
var wafer4 = new Wafer('N22222.00', 'Mobile Phone', 'Feedforward');
var wafer5 = new Wafer('N33333.00', 'NoteBook', 'Recommend');
apc.execute(wafer1, processTool_a);
apc.execute(wafer2, processTool_b);
apc.execute(wafer3, processTool_a);
apc.execute(wafer4, processTool_b);
apc.execute(wafer5, processTool_b);


