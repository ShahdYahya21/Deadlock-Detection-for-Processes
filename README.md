## Deadlock Detection in Resource Allocation  

### Overview  
- This C++ program detects deadlocks in a system where multiple processes request and allocate resources. It reads resource allocation, request, and availability data from files, processes the data, and determines whether a deadlock exists.
---

### Functionality  

#### 1. **Reading Input Data**  
- The program reads three files:
  - **Allocation**: Resources currently allocated to each process.
  - **Request**: Additional resources requested by each process.
  - **Available**: Resources currently available in the system.  
- The data is stored in vectors:
  - `allocation`: 2D vector storing allocated resources per process.
  - `request`: 2D vector storing requested resources per process.
  - `available`: 1D vector storing available resources.  

#### 2. **Data Validation**  
- The program checks if the data is consistent:
  - The number of processes in `allocation` and `request` should match.
  - Each process should have a resource vector of the same length as `available`.  
- If inconsistencies are found, the program prints an error message.  

#### 3. **Deadlock Detection Algorithm**  
- **Mark processes as finished** if their resource requests can be satisfied with the available resources.  
- **Release allocated resources** when a process finishes, increasing the available resources.  
- **Detect deadlock**:
  - If a process's request cannot be met and no progress is made in multiple iterations, the system is in a deadlock.  
  - A set (`set<int>`) tracks processes that are waiting indefinitely for resources.  
  - If the same number of deadlocked processes persists across iterations, a deadlock is confirmed.  

#### 4. **Output Results**  
- **No Deadlock**: The program prints the order in which processes finished execution.  
- **Deadlock Detected**: The program prints the list of deadlocked processes.  
---

### Example Output  

**Case 1: No Deadlock** 

  <img width="1120" alt="image" src="https://github.com/user-attachments/assets/a7107ced-9cdb-406d-b94d-e11b4761a6d1" />
  
**Case 2: Deadlock Detected** (for different resource allocations and requests)  

  <img width="929" alt="image" src="https://github.com/user-attachments/assets/b1bcb627-653a-4c9c-95a2-e956ac7f7080" />



