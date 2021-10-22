package test.model;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import main.model.Contact;

class ContactTest {

	@Test
	void testContact() {
		Contact contact = new Contact("testID", "Michael", "Jordan", "1234567890", "100 Imaginary Street, Apt #15");
		assertTrue(contact.getId().equals("testID"));
		assertTrue(contact.getFirstName().equals("Michael"));
		assertTrue(contact.getLastName().equals("Jordan"));
		assertTrue(contact.getPhoneNumber().equals("1234567890"));
		assertTrue(contact.getAddress().equals("100 Imaginary Street, Apt #15"));
	}
	
	@Test
	void testContactIdTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("testID12345", "Michael", "Jordan", "1234567890", "100 Imaginary Street, Apt #15");
		});
	}
	
	@Test
	void testContactIdIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact(null, "Michael", "Jordan", "1234567890", "100 Imaginary Street, Apt #15");
		});
	}
	
	@Test
	void testContactFirstNameTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("testID", "Christopher", "Jordan", "1234567890", "100 Imaginary Street, Apt #15");
		});
	}
	
	@Test
	void testContactFirstNameIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("testID", null, "Jordan", "1234567890", "100 Imaginary Street, Apt #15");
		});
	}
	
	@Test
	void testContactLastNameTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("testID", "Michael", "Wilhelmsson", "1234567890", "100 Imaginary Street, Apt #15");
		});
	}
	
	@Test
	void testContactLastNameIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("testID", "Michael", null, "1234567890", "100 Imaginary Street, Apt #15");
		});
	}
	
	@Test
	void testContactPhoneNumberTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("testID", "Michael", "Jordan", "12345678902", "100 Imaginary Street, Apt #15");
		});
	}
	
	void testContactPhoneNumberTooShort() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("testID", "Michael", "Jordan", "123456789", "100 Imaginary Street, Apt #15");
		});
	}
	
	@Test
	void testContactPhoneNumberIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("testID", "Michael", "Jordan", null, "100 Imaginary Street, Apt #15");
		});
	}
	
	@Test
	void testContactAddressTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("testID", "Michael", "Jordan", "1234567890", "100 Imaginary Street, Apt #1522");
		});
	}
	
	@Test
	void testContactAddressIsNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Contact("testID", "Michael", "Jordan", "1234567890", null);
		});
	}

}
