import {Wafer} from './Wafer';
import {APC} from './APC';
import {ProcessTool} from './ProcessTool';
import {ReticleJob} from './ToolCommand';


var apc = new APC();
var processTool_a = new ProcessTool('A');
var processTool_b = new ProcessTool('B');

var wafer1 = new Wafer('N12345.00', 'Mobile Phone', 'ByProductStrategy');
var wafer2 = new Wafer('N54321.00', 'Personal Computer', 'ByProductStrategy');
var wafer3 = new Wafer('N11111.00', 'NoteBook', 'ByProductStrategy');
var wafer4 = new Wafer('N22222.00', 'Mobile Phone', 'Feedforward');
var wafer5 = new Wafer('N33333.00', 'NoteBook', 'Recommend');

var reticleJob = new ReticleJob('Check-In');
processTool_a.addJobs(reticleJob);

apc.preview(wafer1, processTool_a);
apc.execute(wafer1, processTool_a);
apc.execute(wafer2, processTool_a);	
apc.execute(wafer3, processTool_a);

var reticleJob = new ReticleJob('Check-Out');
processTool_a.addJobs(reticleJob);

processTool_a.executeCommand();
