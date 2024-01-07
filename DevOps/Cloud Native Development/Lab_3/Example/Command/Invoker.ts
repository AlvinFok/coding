import {Command} from './Command';

export class Invoker{
		public command: Command;				
		
		public setCommand(command: Command): void
		{
				this.command = command;
		}
		
		public executeCommand(): void
		{
				this.command.execute();
		}
}