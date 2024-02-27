import {Product} from './Product';
import {ConcreteProductA} from './Product';
import {ConcreteProductB} from './Product';

export abstract class Creator{
		abstract someOperation(): void;		
		abstract createProduct(): Product;
}

export class ConcreteCreatorA extends Creator{
		public someOperation(): void
		{
				//doNothing
		}
		public createProduct(): Product
		{
				return new ConcreteProductA();
		}
}

export class ConcreteCreatorB extends Creator{
		public someOperation(): void
		{
				//doNothing
		}
		public createProduct(): Product
		{
				return new ConcreteProductB();
		}
}