import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    private static final String FILE_NAME = "gymMembers.txt";

    public static void main(String[] args) {
        Scanner scnr = new Scanner(System.in);
        ArrayList<GymClass> gymMembers = new ArrayList<GymClass>();

        gymMembers.addAll(loadDataFromFile(FILE_NAME));

        while (true) {
            System.out.println();
            System.out.print("Enter name of gym member: (Enter 'q' if you want to quit) ");
            String memberName = scnr.nextLine();
            System.out.println();

            if (memberName.equals("q")) {
                // program checks if user wants to quit.
                break;
            }

            System.out.println("Hello " + memberName + "!\n");

            GymClass existingMember = findMemberByName(gymMembers, memberName);

            if (existingMember != null) {
                updateMemberData(existingMember, scnr);
            } else {
                addNewMember(gymMembers, memberName, scnr);
            }
        }

        writeDataToFile(gymMembers, FILE_NAME);

        scnr.close();
    }

    private static ArrayList<GymClass> loadDataFromFile(String fileName) {
        ArrayList<GymClass> gymMembers = new ArrayList<GymClass>();
        try (Scanner fileScanner = new Scanner(new File(fileName))) {
            while (fileScanner.hasNextLine()) {
                String line = fileScanner.nextLine();
                String[] parts = line.split(",");
                String name = parts[0];
                int fitData = Integer.parseInt(parts[1]);
                int bootData = Integer.parseInt(parts[2]);
                gymMembers.add(new GymClass(name, fitData, bootData));
            }
        } catch (FileNotFoundException e) {
            // File is not found, program won't do anything but if needed it will make a new file. 
        }
        return gymMembers;
    }

    private static GymClass findMemberByName(ArrayList<GymClass> gymMembers, String name) {
        for (GymClass member : gymMembers) {
            if (member.getName().equals(name)) {
                return member;
            }
        }
        return null; 
    }

    private static void updateMemberData(GymClass member, Scanner scnr) {
        while (true) {
            System.out.print("Which class are you attending today? \nFitness Class or Bootcamp?\nFor Fitness Class enter \"fit\" or for Bootcamp enter \"boot\" \nPlease enter: ");
            String attendingClass = scnr.nextLine();
            System.out.println();

            if (attendingClass.equals("fit")) {
                member.fitModifier();
                System.out.println();
                System.out.println("You are attending a fitness class. You have: " + member.getFitData() + " fitness classes remaining.");

            } else if (attendingClass.equals("boot")) {
                member.bootModifier();
                System.out.println();
                System.out.println("You are attending a bootcamp class. You have: " + member.getBootData() + " Bootcamp classes remaining.");

            } else if (attendingClass.equals("q")) {
                break;
            } else {
                System.out.println("[[[[[Incorrect input. Please enter \"fit\", \"boot\", or \"q\"]]]]]\n");
            }
        }
    }

    private static void addNewMember(ArrayList<GymClass> gymMembers, String name, Scanner scnr) {
        GymClass newMember = new GymClass(name);
        updateMemberData(newMember, scnr);
        gymMembers.add(newMember);
    }


    private static void writeDataToFile(ArrayList<GymClass> gymMembers, String fileName) {
        try (FileWriter writer = new FileWriter(fileName)) {
            for (GymClass member : gymMembers) {
                writer.write(member.getName() + "," + member.getFitData() + "," + member.getBootData() + "\n");
            }
            System.out.println("Gym member data written to file successfully.");
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
    }
}