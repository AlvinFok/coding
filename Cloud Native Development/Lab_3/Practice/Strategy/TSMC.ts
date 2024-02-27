import {Wafer} from './Wafer';
import {APC} from './APC';
import {ProcessTool} from './ProcessTool';


var apc = new APC();
var processTool_a = new ProcessTool('A');
var processTool_b = new ProcessTool('B');

var wafer1 = new Wafer('N12345.00', 'Mobile Phone');
var wafer2 = new Wafer('N54321.00', 'Personal Computer');
var wafer3 = new Wafer('N11111.00', 'NoteBook');
apc.execute(wafer1, processTool_a);
apc.execute(wafer2, processTool_b);
apc.execute(wafer3, processTool_a);


