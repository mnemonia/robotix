package com.mnemonia.io;

public interface IoSystemService {
	public Disposable addListener(int pin, IoListener listener);
}
