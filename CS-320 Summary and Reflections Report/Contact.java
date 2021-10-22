package main.model;

public class Contact {
	//The final keyword ensures that the id can be set only at initialization.
	//Additionally, there is no way to access the variable from outside this class.
	private final String contactId;
	private String firstName;
	private String lastName;
	private String phoneNumber;
	private String address;
	
	//This is the only constructor, ensuring that all required fields are populated.
	public Contact(String contactId, String firstName, String lastName, String phoneNumber, String address) {
		if(contactId == null || contactId.length() > 10) {
			throw new IllegalArgumentException("Invalid contact ID.");
		}
		this.contactId = contactId;
		setFirstName(firstName);
		setLastName(lastName);
		setPhoneNumber(phoneNumber);
		setAddress(address);
	}

	public String getFirstName() {
		return firstName;
	}

	public void setFirstName(String firstName) {
		if(firstName == null || firstName.length() > 10) {
			throw new IllegalArgumentException("Invalid contact first name.");
		}
		this.firstName = firstName;
	}

	public String getLastName() {
		return lastName;
	}

	public void setLastName(String lastName) {
		if(lastName == null || lastName.length() > 10) { 
			throw new IllegalArgumentException("Invalid contact last name.");
		}
		this.lastName = lastName;
	}

	public String getPhoneNumber() {
		return phoneNumber;
	}

	public void setPhoneNumber(String phoneNumber) {
		if(phoneNumber == null || phoneNumber.length() != 10) {
			throw new IllegalArgumentException("Invalid contact phone number.");
		}
		this.phoneNumber = phoneNumber;
	}

	public String getAddress() {
		return address;
	}

	public void setAddress(String address) {
		if(address == null || address.length() > 30) {
			throw new IllegalArgumentException("Invalid contact address.");
		}
		this.address = address;
	}

	public String getId() {
		return contactId;
	}
}
