<script lang="ts">
  import Brightness from "./lib/Brightness.svelte";
  import FanSpeed from "./lib/FanSpeed.svelte";
  import RunAnimation from "./lib/RunAnimation.svelte";
  import Message from "./lib/Message.svelte";
  let discoveredIPs: string[] = [];
  let currentIP = "";
  let isOnline = false;
  let isConnecting = false;

  async function testConnection() {
    if (isConnecting) return;
    try {
      // First, get the latest IP list from the Dev Server backend
      let discoverResponse = await fetch('/api/get-ip');
      if (discoverResponse.ok) {
        let json = await discoverResponse.json();
        if (json.ips) {
          discoveredIPs = json.ips;
          // Set the current IP to the first discovered one if currently empty
          if (!currentIP && discoveredIPs.length > 0) {
            currentIP = discoveredIPs[0];
          }
        }
      }

      if (!currentIP) return;

      isConnecting = true;
      let response = await fetch(`${currentIP}/test`);
      if (response.ok) {
        isOnline = true;
      } else {
        isOnline = false;
      }
    } catch (error) {
      isOnline = false;
    }
    isConnecting = false;
  }

  testConnection();
  setInterval(testConnection, 5000);
</script>

<main>
  <div class="status">
    <span class="header">Protogen Control Panel</span>

    {#if discoveredIPs.length === 0}
      <div class="discovery-box">
        <p>📡 <strong>Looking for Protogen...</strong></p>
        <p class="discovery-hint">Make sure your Protogen is turned on and connected to the hotspot.</p>
        <div class="spinner"></div>
      </div>
    {:else}
      <p>
        Your protogen is {#if isOnline}
          💚 <span class="online">online</span>{:else}
          💔 <span class="offline">offline</span
          >{/if}{#if isConnecting}?{:else}.{/if}
      </p>
      
      <div class="ip-selector">
        <label for="ip-select">Connected to:</label>
        {#if discoveredIPs.length === 1}
          <span class="single-ip">{currentIP}</span>
        {:else}
          <select id="ip-select" bind:value={currentIP} on:change={testConnection}>
            {#each discoveredIPs as ip}
              <option value={ip}>{ip}</option>
            {/each}
          </select>
        {/if}
      </div>
    {/if}
  </div>

  <div class="columns" style={discoveredIPs.length === 0 ? "opacity: 0.5; pointer-events: none;" : ""}>
    <div class="column">
      <div>Animations</div>
      <div class="animations">
        <RunAnimation name="squiggle" url={currentIP} />
        <RunAnimation name="hearts" url={currentIP} />
        <RunAnimation name="confuzed" url={currentIP} />
        <RunAnimation name="smile" url={currentIP} />
        <RunAnimation name="blush" url={currentIP} />
        <RunAnimation name="gay" url={currentIP} />
      </div>
    </div>
    <div class="column">
      <div>Brightness</div>
      <Brightness url={currentIP} />
      <div>Fan Speed</div>
      <FanSpeed url={currentIP} /> 
      <Message url={currentIP}/>
    </div>
  </div>
</main>

<style>
  .online {
    color: greenyellow;
  }
  .offline {
    color: red;
  }

  .status {
    border-width: 4px;
    border-style: solid;
    border-color: #1a1a1a;
    border-radius: 8px;
    padding: 4px;
    margin: 4px;
    font-size: 1.2rem;
  }

  .header {
    font-size: 2em;
    margin: 8px;
  }

  .columns {
    display: grid;
    grid-gap: 10px;
    grid-template-columns: 1fr 1fr;
    transition: all 0.3s;
  }

  .discovery-box {
    margin: 20px 0;
    padding: 15px;
    border: 2px dashed #444;
    border-radius: 8px;
    background: rgba(0,0,0,0.2);
  }

  .discovery-hint {
    font-size: 0.9rem;
    color: #888;
    margin-top: 5px;
  }

  .spinner {
    border: 4px solid rgba(255,255,255,0.1);
    width: 30px;
    height: 30px;
    border-radius: 50%;
    border-left-color: #09f;
    animation: spin 1s linear infinite;
    margin: 15px auto;
  }

  @keyframes spin {
    0% { transform: rotate(0deg); }
    100% { transform: rotate(360deg); }
  }

  .ip-selector {
    margin-top: 15px;
    font-size: 0.9rem;
    background: #111;
    padding: 8px;
    border-radius: 4px;
    display: inline-block;
  }

  .single-ip {
    color: #4CAF50;
    font-weight: bold;
    font-family: monospace;
    margin-left: 5px;
  }

  select {
    background: #222;
    color: white;
    border: 1px solid #444;
    padding: 4px;
    border-radius: 4px;
    margin-left: 5px;
  }

  input[type="number"] {
    width: 3rem;
  }
</style>
