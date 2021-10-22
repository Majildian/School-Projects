package main.services;

import java.util.Hashtable;
import java.util.Map;

import main.model.Contact;

public class ContactService {
	private Map<String, Contact> contacts;
	
	public ContactService() {
		this.contacts = new Hashtable<String, Contact>();
	}
	
	public boolean isContactAdded(String contactId) {
		return contacts.containsKey(contactId);
	}
	
	public void addContact(Contact contact) {
		if(contacts.containsKey(contact.getId())) {
			throw new IllegalArgumentException("Service already contains contact.");
		}
		contacts.put(contact.getId(), contact);
	}
	
	public void removeContact(String contactId) {
		//This method does nothing if the key is not present, so we don't need to check for it.
		contacts.remove(contactId);
	}
	
	public void updateContactFirstName(String contactId, String firstName) {
		if(!isContactAdded(contactId)) {
			return;
		}
		Contact contact = contacts.get(contactId);
		contact.setFirstName(firstName);
	}
	
	public void updateContactLastName(String contactId, String lastName) {
		if(!isContactAdded(contactId)) {
			return;
		}
		Contact contact = contacts.get(contactId);
		contact.setLastName(lastName);
	}
	
	public void updateContactPhoneNumber(String contactId, String phoneNumber) {
		if(!isContactAdded(contactId)) {
			return;
		}
		Contact contact = contacts.get(contactId);
		contact.setPhoneNumber(phoneNumber);
	}
	
	public void updateContactAddress(String contactId, String address) {
		if(!isContactAdded(contactId)) {
			return;
		}
		Contact contact = contacts.get(contactId);
		contact.setAddress(address);
	}
	
}
