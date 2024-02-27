export interface Product{
		doStuff(): void;
}

export class ConcreteProductA implements Product{
		public doStuff(): void
		{
				console.log('ConcreteProductA.doStuff()');
		}
}

export class ConcreteProductB implements Product{
		public doStuff(): void
		{
				console.log('ConcreteProductB.doStuff()');
		}
}