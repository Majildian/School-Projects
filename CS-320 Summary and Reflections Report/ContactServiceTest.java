package test.services;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import main.model.Contact;
import main.services.ContactService;

class ContactServiceTest {
	private ContactService serviceTest;
	private Contact testContact;

	@BeforeEach
	void setUp() throws Exception {
		serviceTest = new ContactService();
		testContact = new Contact("testID", "Michael", "Jordan", "1234567890", "100 Imaginary Street, Apt #15");
		serviceTest.addContact(testContact);
	}

	@Test
	void testServiceContainsContact() {
		assertTrue(serviceTest.isContactAdded(testContact.getId()));
	}
	
	@Test
	void testServiceUniqueId() {
		Contact testContact2 = new Contact("testID52", "Michael", "Jordan", "1234567890", "100 Imaginary Street, Apt #15");
		serviceTest.addContact(testContact2);
		assertThrows(IllegalArgumentException.class, () -> {
			serviceTest.addContact(new Contact("testID52", "Michael", "Jordan", "1234567890", "100 Imaginary Street, Apt #15"));
		});
	}
	
	@Test
	void testServiceRemoveContact() {
		serviceTest.removeContact(testContact.getId());
		assertFalse(serviceTest.isContactAdded(testContact.getId()));
	}
	
	@Test
	void testServiceUpdateFirstName() {
		serviceTest.updateContactFirstName(testContact.getId(), "Gerald");
		assertTrue(testContact.getFirstName().equals("Gerald"));
	}
	
	@Test
	void testServiceUpdateLastName() {
		serviceTest.updateContactLastName(testContact.getId(), "Smith");
		assertTrue(testContact.getLastName().equals("Smith"));
	}
	
	@Test
	void testServiceUpdatePhoneNumber() {
		serviceTest.updateContactPhoneNumber(testContact.getId(), "6564543432");
		assertTrue(testContact.getPhoneNumber().equals("6564543432"));
	}
	
	@Test
	void testServiceUpdateAddress() {
		serviceTest.updateContactAddress(testContact.getId(), "End of the Earth");
		assertTrue(testContact.getAddress().equals("End of the Earth"));
	}

}
