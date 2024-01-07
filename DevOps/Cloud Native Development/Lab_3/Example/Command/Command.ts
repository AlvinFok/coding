export interface Command{
		execute(): void;
}

export class Command1 implements Command{
		public execute(): void
		{
				console.log('Command1.execute()');
		}
}

export class Command2 implements Command{
		public execute(): void
		{
				console.log('Command2.execute()');
		}
}